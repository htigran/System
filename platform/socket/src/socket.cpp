//
//  tsocket.cpp
//  Sockets
//
//  Created by Tigran Hovhannisyan on 19/03/2016.
//  Copyright © 2016 TIKO. All rights reserved.
//

#include "socket.hpp"

#include <dbg.hpp>

#include <arpa/inet.h>
#include <iostream>

Socket::Socket()
		: m_state(INITIAL)
{
	m_sockid = ::socket(PF_INET, SOCK_STREAM, 0);
	if (m_sockid > 0) {
		TRACE("Socket created");
	}
}

Socket::Socket(int sockid)
		: 	m_sockid(sockid),
			m_state(INITIAL)
{
	TRACE("Socket created");
}

Socket::~Socket()
{
	if (m_state != CLOSED) {
		//close(m_sockid);
		::shutdown(m_sockid, SHUT_RDWR);
		TRACE("Socket closed");
	}

	TRACE("Socket distracted");
}

Socket::Status Socket::close()
{
	if (m_state != CONNECTED) {
		TRACE("Can't close: Socket is not connected");
		return ECONNECT;
	}

//close(m_sockid);
	if (int e = shutdown(m_sockid, SHUT_RDWR) < 0) {
		TRACE("Can't close: error during shutdown (" << e << ")");
		return ECLOSE;
	}
	m_state = CLOSED;
	TRACE("Socket closed");
	return NOERROR;
}

Socket::Status Socket::connect(	std::string ip,
								int port)
{
	sockaddr_in addrport;
	addrport.sin_family = AF_INET;
	addrport.sin_port = htons(port);
	addrport.sin_addr.s_addr = inet_addr(ip.c_str());
	if (int e = ::connect(m_sockid, (sockaddr *) &addrport, sizeof(addrport))
			< 0) {
		TRACE("Can't connect: (" << e << ")");
		return ECONNECT;
	}
	m_state = CONNECTED;
	TRACE("Connected to: " << ip << " : " << port);
	return NOERROR;
}

Socket::Status Socket::send(const std::string& msg)
{
	if (m_state != CONNECTED) {
		TRACE("Can't send: not connected. Message: " << msg);
		return ECONNECT;
	}

	if (int e = ::send(m_sockid, msg.c_str(), msg.size(), 0) < 0) {
		TRACE("Can't send: (" << e << "). Message: " << msg);
		return ESEND;
	}

	TRACE("Sent: " << msg);
	return NOERROR;
}

Socket::Status Socket::recv(std::string& res)
{
	if (m_state != CONNECTED) {
		TRACE("Can't receive: not connected.");
		return ECONNECT;
	}

	const int msgLen = res.size();
	if (int e = ::recv(m_sockid, &res[0], msgLen, 0) < 0) {
		TRACE("Can't receive: (" << e << ")");
		return ERECIEVE;
	}

	TRACE("received: " << res);
	return NOERROR;
}
