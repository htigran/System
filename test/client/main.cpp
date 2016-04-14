//
//  main.cpp
//  Sockets
//
//  Created by Tigran Hovhannisyan on 13/03/2016.
//  Copyright © 2016 Tigran Hovhannisyan. All rights reserved.
//

#include <iostream>
#include <cassert>

#include <socket.hpp>

int main(	int argc,
			const char * argv[])
{

	Socket client;
	client.connect("127.0.0.1", 5100);
	client.send("Hello");
	return 0;
}
