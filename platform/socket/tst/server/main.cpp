//
//  main.cpp
//  Sockets
//
//  Created by Tigran Hovhannisyan on 13/03/2016.
//  Copyright © 2016 Tigran Hovhannisyan. All rights reserved.
//

#include <iostream>
#include <cassert>

#include <socket_server.hpp>

int main(	int argc,
			const char * argv[])
{

	SocketServer server;
	server.bind(5100);
	server.listen(3);
	Socket clSockId = server.accept();
	clSockId.recv();
	clSockId.close();
	return 0;
}
