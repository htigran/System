/*
 * mutex.cpp
 *
 *  Created on: 28 Mar 2016
 *      Author: tigran
 */

#include <mutex.hpp>

namespace platform
{

Mutex::Mutex()
{
	this->m_mutex = new pthread_mutex_t;
	pthread_mutex_init(m_mutex, NULL);
}

int Mutex::lock()
{
	if (pthread_mutex_lock(m_mutex) < 0)
		return -1;

	return 0;
}

int Mutex::unlock()
{
	if (pthread_mutex_unlock(m_mutex) < 0)
		return -1;

	return 0;
}

int Mutex::tryLock()
{
	if (pthread_mutex_trylock(m_mutex) < 0)
		return -1;

	return 0;
}

int Mutex::destroy()
{
	if (pthread_mutex_destroy(m_mutex) < 0)
		return -1;

	return 0;
}

} /* namespace platform */
