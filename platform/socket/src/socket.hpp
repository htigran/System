//
//  tsocket.hpp
//  Sockets
//
//  Created by Tigran Hovhannisyan on 13/03/2016.
//  Copyright © 2016 Tigran Hovhannisyan. All rights reserved.
//

#ifndef PLATFORM_SOCKET_SRC_SOCKET_HPP_
#define PLATFORM_SOCKET_SRC_SOCKET_HPP_

#include <string>

class Socket
{

public:
    
	/*! \brief Default constructor
	 *
	 *	Creates the socket object in default state.
	 */
    Socket();
    
	/*! \brief Default constructor
	 *
	 *	Creates the socket object in default state.
	 */
    Socket(int sockid);

	/*! \brief Destructor
	 *
	 *	Destroys and closes the socket object.
	 */
    ~Socket();

	/*! \brief initiate a connection on a socket
	 *
	 *  Connects the socket to the address specified by ip and port.
	 *
	 *  \param ip address to the other end
	 *
	 *  \param port number of the other end
	 */
    void connect(std::string ip, int port);

	/*! \brief  send a message on the socket
	 *
	 *  Used to transmit a message to another socket.
	 *
	 *  \param msg message to transmit
	 */
    void send(std::string msg);
    
	/*! \brief receive a message from a socket
	 *
	 *  Detailed description starts here.
	 */
    std::string recv();
    
	/*! \brief Default constructor
	 *
	 *  Detailed description starts here.
	 */
    std::string recv(int sockId);
    
	/*! \brief closes the connection
	 *
	 *  ...
	 */
    void close();

private:
    int m_sockid;
    
};

#endif /* PLATFORM_SOCKET_SRC_SOCKET_HPP_ */
