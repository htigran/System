/*
 * semaphore.cpp
 *
 *  Created on: 28 Mar 2016
 *      Author: tigran
 */

#include <semaphore.hpp>

namespace platform
{

Semaphore::Semaphore(	char name[],
						unsigned int val)
{
	sem_unlink(name);
	this->name = name;
	this->sem = sem_open(name, O_CREAT | O_EXCL, 0666, val);
}

int Semaphore::wait()
{
	return (sem_wait(sem));
}

int Semaphore::post()
{
	return (sem_post(sem));
}

int Semaphore::tryWait()
{
	return (sem_trywait(sem));
}

void Semaphore::close()
{
	sem_close(sem);
	sem_unlink(name);
}

} /* namespace platform */
