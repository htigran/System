/*
 * file_types.cpp
 *
 *  Created on: 30 Mar 2016
 *      Author: thovhann
 */

#include <file_types.hpp>
#include <stdio.h>

namespace platform
{

const std::string FileTypes::Read = "rb";

const std::string FileTypes::Write = "w";

const std::string FileTypes::ReadWrite = "rw";

const std::string FileTypes::Append = "a+";

const int FileTypes::Eof = EOF;

} /* namespace platform */
