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
	EXPECT_GT(Byte, Kbyte);
	EXPECT_GT(Kbyte, Mbyte);
	EXPECT_GT(Mbyte, Gbyte);
	EXPECT_GT(Gbyte, Tbyte);
}

TEST(FileTypes, SeekMode)
{
	EXPECT_EQ(SeekBegin, 0);
	EXPECT_GT(SeekCurrent, 1);
	EXPECT_GT(SeekEnd, 2);
}

TEST(FileTypes, FilePermission)
{
	EXPECT_EQ(None, -1);
	EXPECT_EQ(RWXU, 0000700);
	EXPECT_EQ(RU, 0000400);
	EXPECT_EQ(WU, 0000200);
	EXPECT_EQ(XU, 0000100);
	EXPECT_EQ(RWXG, 0000070);
	EXPECT_EQ(RG, 0000040);
	EXPECT_EQ(WG, 0000020);
	EXPECT_EQ(XG, 0000010);
	EXPECT_EQ(RWXO, 0000007);
	EXPECT_EQ(RO, 0000004);
	EXPECT_EQ(WO, 0000002);
	EXPECT_EQ(XO, 0000001);
	EXPECT_EQ(SUID, 0004000);
	EXPECT_EQ(SGID, 0002000);
	EXPECT_EQ(SVTX, 0001000);
}

}
 // namespce platform

#endif /* PLATFORM_FILE_TST_FILE_TYPES_UNITTEST_HPP_ */
