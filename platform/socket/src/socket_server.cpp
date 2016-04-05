/*
 * socket_server.cpp
 *
 *  Created on: 23 Mar 2016
 *      Author: thovhann
 */

#include "socket_server.hpp"

#include <dbg.hpp>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>

SocketServer::SocketServer()
{
	m_sockid = ::socket(PF_INET, SOCK_STREAM, 0);
	if (m_sockid > 0) {
		m_state = CREATED;
		TRACE("Socket created");
	}
}

SocketServer::~SocketServer()
{
	if(m_state != CLOSED) {
		close();
	}
}

SocketServer::Status
SocketServer::close()
{
	if(m_state != CREATED) {
		return ECREATE;
	}

	//close(m_sockid);
	if (shutdown(m_sockid, SHUT_RDWR) < 0) {
		return ECLOSE;
	}

	m_state = CLOSED;
	TRACE("Socket closed");
	return NOERROR;
}

SocketServer::Status
SocketServer::bind(uint16_t port)
{
    if (m_state != CREATED) {
        return ECREATE;
    }
    bzero((char*) &m_serverAddr, sizeof(m_serverAddr));
    m_serverAddr.sin_family = AF_INET;
    m_serverAddr.sin_port = htons(port);
    m_serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (::bind(m_sockid, (sockaddr*) &m_serverAddr, sizeof(m_serverAddr)) < 0) {
        return EBIND;
    }

	m_state = BINDED;
	TRACE("Binded to port: " << port);
    return NOERROR;
}

SocketServer::Status
SocketServer::listen(int backlog)
{
    if (m_state != BINDED) {
        return EBIND;
    }
	if (::listen(m_sockid, backlog) < 0) {
		return ELISTEN;
	}

	m_state = LISTEN;
	TRACE("Listening for max " << backlog << " connections.");
	return NOERROR;
}

SocketServer::Status
SocketServer::accept(Socket& accepted)
{
	if (m_state != LISTEN) {
		return ELISTEN;
	}
	sockaddr_in addrport;
	socklen_t addrlen = sizeof(addrport);
	int newsockt = ::accept(m_sockid, (sockaddr *) &addrport, &addrlen);
	if (newsockt < 0) {
		return EACCEPT;
	}
	accepted = newsockt;


	TRACE("Accepted connection");
	return NOERROR;
}

