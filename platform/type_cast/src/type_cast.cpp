/*
 * type_cast.cpp
 *
 *  Created on: 28 Mar 2016
 *      Author: tigran
 */

#include <type_cast.hpp>

namespace platform
{

string TypeCast::toString(int i)
{
	stringstream oss;
	oss << i;
	return (oss.str());
}

string TypeCast::toString(long i)
{
	stringstream oss;
	oss << i;
	return (oss.str());
}

string TypeCast::toString(float i)
{
	stringstream oss;
	oss << i;
	return (oss.str());
}

string TypeCast::toString(char c)
{
	stringstream oss;
	oss << c;
	return (oss.str());
}

int TypeCast::toInt(string s)
{
	return 0;
}

} /* namespace platform */
