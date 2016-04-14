/*
 * file_mode.cpp
 *
 *  Created on: 30 Mar 2016
 *      Author: thovhann
 */

#include "../inc/file_mode.hpp"

namespace platform
{

FileMode::FileMode(FilePermission mode)
		: m_mode(mode)
{
}

FileMode::FileMode(int mode)
		: m_mode(mode)
{
}

FileMode::operator int()
{
	return m_mode;
}

int FileMode::getMode()
{
	return m_mode;
}

string FileMode::getStringMode()
{
	char temp[] = {'-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'};

	if (m_mode == FileTypes::None) {
		return temp;
	}

	if (m_mode & FileTypes::RU) {
		temp[0] = 'r';
	}

	if (m_mode & FileTypes::WU) {
		temp[1] = 'w';
	}

	if (m_mode & FileTypes::XU) {
		temp[2] = 'x';
	}

	if (m_mode & FileTypes::RG) {
		temp[3] = 'r';
	}

	if (m_mode & FileTypes::WG) {
		temp[4] = 'w';
	}

	if (m_mode & FileTypes::XG) {
		temp[5] = 'x';
	}

	if (m_mode & FileTypes::RO) {
		temp[6] = 'r';
	}

	if (m_mode & FileTypes::WO) {
		temp[7] = 'w';
	}

	if (m_mode & FileTypes::XO) {
		temp[8] = 'x';
	}

	return string(temp);
}

} /* namespace platform */
