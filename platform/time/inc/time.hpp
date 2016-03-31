/*
 * time.hpp
 *
 *  Created on: 28 Mar 2016
 *      Author: tigran
 */

#ifndef PLATFORM_TIME_INC_TIME_HPP_
#define PLATFORM_TIME_INC_TIME_HPP_

#include <sys/time.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

namespace platform
{

/**
 * @brief System Time class
 */
class Time
{
public:

	/**
	 * @brief returns the system time in milliseconds
	 * @return a long containing the time
	 */
	static long getTimeMilliseconds();

	/**
	 * @brief returns the time and date formatted
	 * (i.e Wed Oct 12 19:43:44 2011)
	 * @return the string containing the formated date
	 */
	static string getTimeDate();

	/**
	 * @brief returns the time and date formatted by the format string
	 * @param format: the format (eg dd/MM/YYYY - HH:mm::SS).
	 * You can use all formats you want the only restriction is to use
	 * dd for the day
	 * MM for the month
	 * YYYY for the year
	 * HH for the hour
	 * mm for the minutes
	 * SS for the seconds
	 */
	static string getTimeDate(string format);

};

} /* namespace platform */

#endif /* PLATFORM_TIME_INC_TIME_HPP_ */
