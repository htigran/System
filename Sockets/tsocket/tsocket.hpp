//
//  tsocket.hpp
//  Sockets
//
//  Created by Tigran Hovhannisyan on 13/03/2016.
//  Copyright © 2016 Tigran Hovhannisyan. All rights reserved.
//

#ifndef tsocket_hpp
#define tsocket_hpp

#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>

#include "dbg.hpp"

#define SAFE(A) \
if ((A) == -1) { \
    std::cerr << "tsocket error" << __LINE__ << std::endl; \
    exit(5); \
}



class tsocket
{
private:
    int m_sockid;
    int m_queueLimit;
    
public:
    
    tsocket()
    : m_queueLimit(1)
    {
        m_sockid = socket(PF_INET, SOCK_STREAM, 0);
        DBG_MESSAGE("Socket created");
    }
    
    ~tsocket() {
        SAFE(close(m_sockid));
        DBG_MESSAGE("Socket closed");
    }
    
    void bind(int port) {
        sockaddr_in addrport;
        addrport.sin_family = AF_INET;
        addrport.sin_port = htons(port);
        addrport.sin_addr.s_addr = htonl(INADDR_ANY);
        SAFE(::bind(m_sockid, (sockaddr *)&addrport, sizeof(addrport)));
        DBG_MESSAGE("Binded to port: " << port);
    }
    
    void listen() {
        SAFE(::listen(m_sockid, m_queueLimit));
        DBG_MESSAGE("Waiting for max " << m_queueLimit << " connections.");
    }
    
    void connect(std::string ip, int port)
    {
        sockaddr_in addrport;
        addrport.sin_family = AF_INET;
        addrport.sin_port = htons(port);
        addrport.sin_addr.s_addr = inet_addr(ip.c_str());
        ::connect(m_sockid, (sockaddr *)&addrport, sizeof(addrport));
    }
    
    int accept() {
        sockaddr_in addrport;
        socklen_t addrlen = sizeof(addrport);
        int newsockt = ::accept(m_sockid, (sockaddr *)&addrport, &addrlen);
        DBG_MESSAGE("Accepted connection");
        return newsockt;
    }
    
    void send(std::string str) {
        SAFE(::send(m_sockid, str.c_str(), str.size(), 0));
        DBG_MESSAGE("Sent: " << str);
    }
    
    std::string recv() {
        return recv(m_sockid);
    }
    
    std::string recv(int sockId) {
        const int msgLen = 255;
        std::string res;
        res.resize(msgLen);
        SAFE(::recv(sockId, &res[0], msgLen, 0));
        DBG_MESSAGE("received: " << res);
        return res;
    }
    
    void setListenersLimit(int maxListeners) {
        m_queueLimit = maxListeners;
        DBG_MESSAGE("Set max connections limit: " << maxListeners);
    }
    
};

#endif /* tsocket_hpp */
