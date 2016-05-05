/*
 * file_types.hpp
 *
 *  Created on: 29 Apr 2016
 *      Author: thovhann
 */

#ifndef PLATFORM_FILE_TST_FILE_TYPES_UNITTEST_HPP_
#define PLATFORM_FILE_TST_FILE_TYPES_UNITTEST_HPP_

#include <gtest/gtest.h>

namespace platformTest
{

using namespace platform;

//////////////////////////////////////////////////////
// FileTypes
//////////////////////////////////////////////////////
TEST(FileTypes, ConstChecksos)
{
	EXPECT_STREQ(FileTypes::Read.c_str(), "rb");
	EXPECT_STREQ(FileTypes::Write.c_str(), "w");
	EXPECT_STREQ(FileTypes::ReadWrite.c_str(), "rw");
	EXPECT_STREQ(FileTypes::Append.c_str(), "a+");
	EXPECT_EQ(FileTypes::Eof, -2);
}

TEST(FileTypes, SizeFormat)
{
	EXPECT_GT(FileTypes::Byte, FileTypes::Kbyte);
	EXPECT_GT(FileTypes::Kbyte, FileTypes::Mbyte);
	EXPECT_GT(FileTypes::Mbyte, FileTypes::Gbyte);
	EXPECT_GT(FileTypes::Gbyte, FileTypes::Tbyte);
}

TEST(FileTypes, SeekMode)
{
	EXPECT_EQ(FileTypes::SeekBegin, 0);
	EXPECT_GT(FileTypes::SeekCurrent, 1);
	EXPECT_GT(FileTypes::SeekEnd, 2);
}

TEST(FileTypes, FilePermission)
{
	EXPECT_EQ(FileTypes::None, -1);
	EXPECT_EQ(FileTypes::RWXU, 0000700);
	EXPECT_EQ(FileTypes::RU, 0000400);
	EXPECT_EQ(FileTypes::WU, 0000200);
	EXPECT_EQ(FileTypes::XU, 0000100);
	EXPECT_EQ(FileTypes::RWXG, 0000070);
	EXPECT_EQ(FileTypes::RG, 0000040);
	EXPECT_EQ(FileTypes::WG, 0000020);
	EXPECT_EQ(FileTypes::XG, 0000010);
	EXPECT_EQ(FileTypes::RWXO, 0000007);
	EXPECT_EQ(FileTypes::RO, 0000004);
	EXPECT_EQ(FileTypes::WO, 0000002);
	EXPECT_EQ(FileTypes::XO, 0000001);
	EXPECT_EQ(FileTypes::SUID, 0004000);
	EXPECT_EQ(FileTypes::SGID, 0002000);
	EXPECT_EQ(FileTypes::SVTX, 0001000);
}

}
 // namespce platform

#endif /* PLATFORM_FILE_TST_FILE_TYPES_UNITTEST_HPP_ */
