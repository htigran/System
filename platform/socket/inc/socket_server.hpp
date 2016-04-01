/*
 * socket_server.h
 *
 *  Created on: 23 Mar 2016
 *      Author: thovhann
 */

#ifndef PLATFORM_SOCKET_SRC_SOCKET_SERVER_HPP_
#define PLATFORM_SOCKET_SRC_SOCKET_SERVER_HPP_

#include <socket.hpp>

#include <inttypes.h>

class SocketServer
{
public:

	enum Status {
		NOERROR = 0,
		ECREATE,
		EBIND,
		ELISTEN,
		EACCEPT,
		ECLOSE,
	};

	/*! \brief default constructor
	 *
	 */
	SocketServer();

	/*! \brief destructor
	 *
	 */
	virtual ~SocketServer();

	/*! \brief bind a port to the socket
	 *
	 *	\param port number
	 */
	Status bind(uint16_t port);

	/*! \brief listen for connections on a socket
	 *
	 *   Marks the socket as a passive socket, that is, as a socket that will
	 *   be used to accept incoming connection requests using accept().
	 *
	 *  \param backlog defines the maximum length to which the queue of pending
	 *  				connections for the socket may grow
	 */
	Status listen(int backlog);

	/*! \brief accept a connection on the socket
	 *
	 *  It extracts the first connection request on the queue of pending
	 *  connections for the listening socket, creates a new connected socket,
	 *  and returns a new file descriptor referring to that socket. The newly
	 *  created socket is not in the listening state. The original socket
	 *  is unaffected by this call.
	 *
	 *	\return On success, these system calls return a nonnegative integer
	 *	that is a descriptor for the accepted socket. On error, -1 is returned.
	 */
	Status accept(Socket&);

	/*! \brief closes the connection
	 *
	 *  ...
	 */
	Status close();

private:
	int m_sockid;
	sockaddr_in m_serverAddr;

	enum State {
		CREATED,
		BINDED,
		LISTEN,
		CLOSED,
	};

	State m_state;

};

#endif /* PLATFORM_SOCKET_SRC_SOCKET_SERVER_HPP_ */
