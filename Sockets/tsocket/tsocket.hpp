//
//  tsocket.hpp
//  Sockets
//
//  Created by Tigran Hovhannisyan on 13/03/2016.
//  Copyright © 2016 Tigran Hovhannisyan. All rights reserved.
//

#ifndef tsocket_hpp
#define tsocket_hpp

#include "dbg.hpp"

#include <string>

class tsocket
{

public:
    
    tsocket();
    
    ~tsocket();
    
    void bind(int port);
    
    void listen();
    
    void connect(std::string ip, int port);
    
    int accept();
    
    void send(std::string str);
    
    std::string recv();
    
    std::string recv(int sockId);
    
    void setListenersLimit(int maxListeners);
    
    
private:
    int m_sockid;
    int m_queueLimit;
    
};

#endif /* tsocket_hpp */
