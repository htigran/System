//
//  tsocket.cpp
//  Sockets
//
//  Created by Tigran Hovhannisyan on 19/03/2016.
//  Copyright © 2016 TIKO. All rights reserved.
//

#include "socket.hpp"

#include <dbg.hpp>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>


Socket::Socket(int sockid)
		: m_sockid(sockid)
{
}

Socket::~Socket()
{
	if(m_state != CLOSED) {
		//close(m_sockid);
		::shutdown(m_sockid, SHUT_RDWR);
	}

	TRACE("Socket distracted");
}

Socket::Status
Socket::close()
{
	if(m_state != CONNECTED) {
		return ECONNECT;
	}

	//close(m_sockid);
	if (shutdown(m_sockid, SHUT_RDWR) < 0) {
		return ECLOSE;
	}
	m_state = CLOSED;
	TRACE("Socket closed");
	return NOERROR;
}

Socket::Status
Socket::connect(	std::string ip,
						int port)
{
	sockaddr_in addrport;
	addrport.sin_family = AF_INET;
	addrport.sin_port = htons(port);
	addrport.sin_addr.s_addr = inet_addr(ip.c_str());
	if (::connect(m_sockid, (sockaddr *) &addrport, sizeof(addrport)) < 0) {
		return ECONNECT;
	}
	m_state = CONNECTED;
	TRACE("Connected to: " << ip << " : " << port);
	return NOERROR;
}

Socket::Status
Socket::send(std::string str)
{
	if(m_state != CONNECTED) {
		return ECONNECT;
	}

	if (::send(m_sockid, str.c_str(), str.size(), 0) < 0) {
		return ESEND;
	}

	TRACE("Sent: " << str);
	return NOERROR;
}

Socket::Status
Socket::recv(std::string& res)
{
	if(m_state != CONNECTED) {
		return ECONNECT;
	}

	const int msgLen = res.size();
	if (::recv(sockId, &res[0], msgLen, 0) < 0) {
		return ERECIEVE;
	}

	TRACE("received: " << res);
	return NOERROR;
}
