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
    }
    
    ~tsocket() {
        int status = close(m_sockid);
        if (status != 0) {
            std::cerr << "Can't close the socket" << std::endl;
            exit(-5);
        }
#ifdef DEBUG
        else {
            std::cout << "Socket created" << std::endl;
        }
#endif
    }
    
    void bind(int port) {
        sockaddr_in addrport;
        addrport.sin_family = AF_INET;
        addrport.sin_port = htons(port);
        addrport.sin_addr.s_addr = htonl(INADDR_ANY);
        if (::bind (m_sockid, (sockaddr *)&addrport, sizeof(addrport)) != 0) {
            std::cerr << "Can't bind the port" << std::endl;
            exit(-1);
        }
#ifdef DEBUG
        else {
            std::cout << "Binded to port: " << port << std::endl;
        }
#endif
    }
    
    void listen() {
        int status = ::listen(m_sockid, m_queueLimit);
        if (0 != status) {
            std::cerr << "Can't listen to socket" << std::endl;
            exit(-2);
        }
#ifdef DEBUG
        else {
            std::cout << "listening" << std::endl;
        }
#endif
    }
    
    void connect(std::string ip, int port)
    {
        sockaddr_in addrport;
        addrport.sin_family = AF_INET;
        addrport.sin_port = htons(port);
        addrport.sin_addr.s_addr = inet_addr(ip.c_str());
        ::connect(m_sockid, (sockaddr *)&addrport, sizeof(addrport));
    }
    
    void accept() {
        sockaddr_in addrport;
        socklen_t addrlen = sizeof(addrport);
        ::accept(m_sockid, (sockaddr *)&addrport, &addrlen);
#ifdef DEBUG
        std::cout << "accepted" << std::endl;
#endif
    }
    
    void send(std::string str) {
        ssize_t count = ::send(m_sockid, str.c_str(), str.size(), 0);
        if (-1 == count) {
            std::cerr << "Can't send message: " << str << std::endl;
            exit(-3);
        }
#ifdef DEBUG
        else {
            std::cout << "sent: " << str << std::endl;
        }
#endif
    }
    
    std::string recv() {
        int msgLen = 255;
        std::string res;
        res.reserve(msgLen);
        ssize_t count = ::recv(m_sockid, &res[0], msgLen, 0);
        if (-1 == count) {
            std::cerr << "Can't recieve message" << std::endl;
            exit(-4);
        }
#ifdef DEBUG
        else {
            std::cout << "received: " << res << std::endl;
        }
#endif
        
        return res; // TODO skip buffer copy
    }
    
    void setListenersLimit(int maxListeners) {
        m_queueLimit = maxListeners;
#ifdef DEBUG
        std::cout << "Max clients number set: " << maxListeners << std::endl;
#endif
    }
    
};

#endif /* tsocket_hpp */
