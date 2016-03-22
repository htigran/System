//
//  tsocket.cpp
//  Sockets
//
//  Created by Tigran Hovhannisyan on 19/03/2016.
//  Copyright © 2016 TIKO. All rights reserved.
//

#include "tsocket.hpp"

#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>

#include "dbg.hpp"

#define SAFE(A) \
if ((A) == -1) { \
std::cerr << "tsocket error" << __LINE__ << std::endl; \
exit(5); \
}


tsocket::tsocket()
: m_queueLimit(1)
{
    m_sockid = socket(PF_INET, SOCK_STREAM, 0);
    TRACE("Socket created");
}

tsocket::~tsocket() {
    SAFE(close(m_sockid));
    TRACE("Socket closed");
}

void tsocket::bind(int port) {
    sockaddr_in addrport;
    addrport.sin_family = AF_INET;
    addrport.sin_port = htons(port);
    addrport.sin_addr.s_addr = htonl(INADDR_ANY);
    SAFE(::bind(m_sockid, (sockaddr *)&addrport, sizeof(addrport)));
    TRACE("Binded to port: " << port);
}

void tsocket::listen() {
    SAFE(::listen(m_sockid, m_queueLimit));
    TRACE("Waiting for max " << m_queueLimit << " connections.");
}

void tsocket::connect(std::string ip, int port)
{
    sockaddr_in addrport;
    addrport.sin_family = AF_INET;
    addrport.sin_port = htons(port);
    addrport.sin_addr.s_addr = inet_addr(ip.c_str());
    ::connect(m_sockid, (sockaddr *)&addrport, sizeof(addrport));
}

int tsocket::accept() {
    sockaddr_in addrport;
    socklen_t addrlen = sizeof(addrport);
    int newsockt = ::accept(m_sockid, (sockaddr *)&addrport, &addrlen);
    TRACE("Accepted connection");
    return newsockt;
}

void tsocket::send(std::string str) {
    SAFE(::send(m_sockid, str.c_str(), str.size(), 0));
    TRACE("Sent: " << str);
}

std::string tsocket::recv() {
    return recv(m_sockid);
}

std::string tsocket::recv(int sockId) {
    const int msgLen = 255;
    std::string res;
    res.resize(msgLen);
    SAFE(::recv(sockId, &res[0], msgLen, 0));
    TRACE("received: " << res);
    return res;
}

void tsocket::setListenersLimit(int maxListeners) {
    m_queueLimit = maxListeners;
    TRACE("Set max connections limit: " << maxListeners);
}
