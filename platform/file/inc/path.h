/*
 * path.h
 *
 *  Created on: 30 Mar 2016
 *      Author: thovhann
 */

#ifndef PLATFORM_FILE_INC_PATH_H_
#define PLATFORM_FILE_INC_PATH_H_

#include <iostream>
using namespace std;

namespace platform
{

/**
 * @brief Represents a Path
 */
class Path
{
public:
	Path(string path);

	/**
	 * @brief get the absolute path of the file
	 * @return the absolute path of the file
	 */
	Path getAbsolutePath();

	/**
	 * @brief gets the file name of the file
	 * @return the name
	 */
	string getName();

	/**
	 * @brief gets the parent directory
	 * @return a Path object containing the parent path. If not parent ('/') the same path is returned
	 */
	Path getParent();

	/**
	 * @brief gets the path in string format
	 * @return the string containing the path
	 */
	string toString();

	/**
	 * @brief allows (char*) cast
	 */
	operator const char*();

private:
	string m_path;
};

} /* namespace platform */

#endif /* PLATFORM_FILE_INC_PATH_H_ */
