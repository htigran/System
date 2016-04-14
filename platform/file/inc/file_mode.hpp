/*
 * file_mode.h
 *
 *  Created on: 30 Mar 2016
 *      Author: thovhann
 */

#ifndef PLATFORM_FILE_FILE_MODE_H_
#define PLATFORM_FILE_FILE_MODE_H_

#include <iostream>
#include "file_types.hpp"

using namespace std;

namespace platform
{

/**
 * @brief Represents the file permissions
 */
class FileMode : public FileTypes
{
public:
	/**
	 * @brief Constructor
	 * @param mode the FilePermission
	 */
	FileMode(FilePermission mode);

	/**
	 * @brief Constructor
	 * @param mode the mode in int format (ex: 0744)
	 */
	FileMode(int mode);

	/**
	 * @brief get the mode of the file in int format
	 * @return the mode
	 * @see FileTypes for modes declaration
	 */
	int getMode();

	/**
	 * @brief allows the (char*) cast of the object
	 */
	operator int();

	/**
	 * @brief converts the mode to string representation (ex: 0755 -> rwxr-xr-x)
	 * @return the string representation of the mode or empty string if error occurs
	 */
	string getStringMode();

private:
	int m_mode;
	string m_path;

};

} /* namespace platform */

#endif /* PLATFORM_FILE_FILE_MODE_H_ */
