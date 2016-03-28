/*
 * thread.hpp
 *
 *  Created on: 28 Mar 2016
 *      Author: tigran
 */

#ifndef PLATFORM_THREAD_SRC_THREAD_HPP_
#define PLATFORM_THREAD_SRC_THREAD_HPP_

#include <pthread.h>

namespace platform
{

class Thread
{
public:
	/**
	 * @brief starts the thread and executes the run method
	 * @return 0 if success, -1 otherwise
	 */
	int start();

	/**
	 * @brief Causes the calling thread to wait for the termination of the specified
	 * thread
	 */
	void* join();

	/**
	 * @brief Used to indicate to the implementation that storage for the
	 * thread can be reclaimed when the thread terminates.
	 * If thread has not terminated, detach() will not cause it to terminate
	 * @return 0 if success and a value < 0 if failure
	 */
	int detach();

	/**
	 * @brief tests if the 2 threads are the same
	 * @return true is equals, false otherwise
	 */
	int equals(Thread* t);

	/**
	 * @brief The exit method terminates the calling thread
	 */
	void exit(void* value_ptr);

	/**
	 * @brief The cancel() method requests that thread be canceled.
	 * The target thread's cancelability state and type determines when
	 * the cancellation takes effect.
	 * When the cancellation is acted on, the cancellation cleanup handlers
	 * for thread are called.  When the last cancellation cleanup handler returns, the
	 * thread-specific data destructor functions will be called for thread.
	 * When the last destructor function returns, thread will be terminated.a
	 */
	int cancel();

	/**
	 * @brief returns the pthread
	 */
	pthread_t getThread();

	virtual ~Thread();

protected:
	virtual void run() = 0;

private:
	static void* go(void* obj);
	pthread_t m_thread;

};

} /* namespace platform */

#endif /* PLATFORM_THREAD_SRC_THREAD_HPP_ */
