/*
 * logger.hpp
 *
 *  Created on: 28 Mar 2016
 *      Author: tigran
 */

#ifndef PLATFORM_LOGGER_INC_LOGGER_HPP_
#define PLATFORM_LOGGER_INC_LOGGER_HPP_

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

namespace platform
{

/**
 * @brief Logger for logging different events (errors, ...)
 */
class Logger
{
public:
	/**
	 * @brief Constructor
	 * @param name the path to the log file.
	 * If the file does not exist, it will be created, otherwise, it will be openned in append mode
	 */
	Logger(std::string name);

	/**
	 * @brief Virtual destructor
	 */
	virtual ~Logger();

	/**
	 * @brief Log the stream input
	 * @param type: the Type of data to log (i.e. DEBUG, ERROR, ...)
	 * @param indent the indent level
	 */
	std::ofstream& log(std::string type, int indent = 0);

private:
	std::string getTimeDate();
	std::ofstream m_out;

};

} /* namespace platform */

#endif /* PLATFORM_LOGGER_INC_LOGGER_HPP_ */
