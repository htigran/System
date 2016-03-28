/*
 * mutex.hpp
 *
 *  Created on: 28 Mar 2016
 *      Author: tigran
 */

#ifndef PLATFORM_MUTEX_INC_MUTEX_HPP_
#define PLATFORM_MUTEX_INC_MUTEX_HPP_

#include <pthread.h>

namespace platform
{

/**
 * @brief Mutex implementation
 */
class Mutex
{
public:
	/**
	 * @brief Constructor
	 */
	Mutex();

	/**
	 * @brief locks the mutex.  If the mutex is already locked, the calling thread will block until the mutex becomes available.
	 * @return  If successful, lock() will return zero.  Otherwise, an error number will be returned to indicate the error.
	 */
	int lock();

	/**
	 * @brief The trylock() method locks mutex.  If the mutex is already locked, trylock() will not block waiting for the mutex, but will return an error condition
	 * @return  If successful, trylock() will return zero.  Otherwise, an error number will be returned to indicate the error.
	 */
	int tryLock();

	/**
	 * @brief  If the current thread holds the lock on mutex, then the unlock() function unlocks mutex.
	 * Calling unlock() with a mutex that the calling thread does not hold will result in undefined behavior.
	 * @return  If successful, unlock() will return zero.  Otherwise, an error number will be returned to indicate the error.
	 */
	int unlock();

	/**
	 * @brief The destroy() method frees the resources allocated for mutex.
	 * @return  If successful, destroy() will return zero.  Otherwise, an error number will be returned to indicate the error.
	 */
	int destroy();

private:
	pthread_mutex_t* m_mutex;

};

} /* namespace platform */

#endif /* PLATFORM_MUTEX_INC_MUTEX_HPP_ */
