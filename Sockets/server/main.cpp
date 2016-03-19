//
//  main.cpp
//  Sockets
//
//  Created by Tigran Hovhannisyan on 13/03/2016.
//  Copyright © 2016 Tigran Hovhannisyan. All rights reserved.
//

#include "tsocket.hpp"

#include <iostream>
#include <cassert>


int main(int argc, const char * argv[]) {
    
    tsocket server;
    server.bind(5100);
    server.listen();
    int clSockId = server.accept();
    server.recv(clSockId);
    close (clSockId);
    return 0;
}