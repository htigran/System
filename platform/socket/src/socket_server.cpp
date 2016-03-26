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

SocketServer::SocketServer() {
    m_sockid = socket(PF_INET, SOCK_STREAM, 0);
    TRACE("Socket created");
}

SocketServer::~SocketServer() {
}

void SocketServer::bind(uint16_t port) {
    sockaddr_in addrport;
    addrport.sin_family = AF_INET;
    addrport.sin_port = htons(port);
    addrport.sin_addr.s_addr = htonl(INADDR_ANY);
    SAFE(::bind(m_sockid, (sockaddr *)&addrport, sizeof(addrport)));
    TRACE("Binded to port: " << port);
}

void SocketServer::listen(int backlog) {
    SAFE(::listen(m_sockid, backlog));
    TRACE("Waiting for max " << backlog << " connections.");
}

Socket SocketServer::accept() {
    sockaddr_in addrport;
    socklen_t addrlen = sizeof(addrport);
    int newsockt = ::accept(m_sockid, (sockaddr *)&addrport, &addrlen);
    TRACE("Accepted connection");
    return Socket(newsockt);
}

