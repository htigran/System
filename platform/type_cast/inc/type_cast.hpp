/*
 * type_cast.hpp
 *
 *  Created on: 28 Mar 2016
 *      Author: tigran
 */

#ifndef PLATFORM_TYPE_CAST_INC_TYPE_CAST_HPP_
#define PLATFORM_TYPE_CAST_INC_TYPE_CAST_HPP_

#include <iostream>
#include <sstream>
using namespace std;

namespace platform
{

/**
 * @brief Allows types cast
 */
class TypeCast
{
public:
	/**
	 * @brief Converts an int to a string
	 * @return the int converted to string
	 */
	static string toString(int);

	/**
	 * @brief Converts a char to a String
	 * @return the converted to string
	 */
	static string toString(char);
	static string toString(long);
	static string toString(float);

	static int toInt(string);
};

} /* namespace platform */

#endif /* PLATFORM_TYPE_CAST_INC_TYPE_CAST_HPP_ */
