/*
 * logger.cpp
 *
 *  Created on: 28 Mar 2016
 *      Author: tigran
 */

#include <time.hpp>
#include <logger.hpp>

using namespace std;

namespace platform
{

Logger::Logger(string path)
{
	m_out.open(path.c_str(), ofstream::app | ofstream::out);
}

std::ofstream& Logger::log(string type, int indent)
{
	int i = 0;

	while (i < indent)
	{
		m_out << "\t";
		i++;
	}

	m_out << endl << "[ " << type << " ] " << "[ ON " << getTimeDate()
			<< " ]\t";
	return m_out;
}

string Logger::getTimeDate()
{
	return Time::getTimeDate("dd/MM/YYYY - HH:mm:SS");
}

Logger::~Logger()
{
	m_out << endl;
	m_out.flush();
	m_out.close();
}

} /* namespace platform */
