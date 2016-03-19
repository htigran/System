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
    
    tsocket client;
    client.bind(5100);
    client.listen();
    client.accept();
    std::cout << client.recv() << std::endl;
    return 0;
}