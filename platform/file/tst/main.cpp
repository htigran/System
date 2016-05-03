/*
 * file_test.cpp
 *
 *  Created on: 28 Mar 2016
 *      Author: tigran
 */

#include <file.hpp>

#include <gtest/gtest.h>

namespace platform
{

//////////////////////////////////////////////////////
// FileMode
//////////////////////////////////////////////////////
TEST(FileMode, Int)
{
	FileMode f(1);
	EXPECT_EQ((int )f, 1);
	EXPECT_EQ(f.getMode(), 1);
	EXPECT_STREQ(f.getStringMode().c_str(), "--------x");
}

TEST(FileMode, FilePermission)
{
	FileMode fxo(FileMode::XO);
	EXPECT_EQ((int )fxo, FileMode::XO);
	EXPECT_EQ(fxo.getMode(), FileMode::XO);
	EXPECT_STREQ(fxo.getStringMode().c_str(), "--------x");

	FileMode fro(FileMode::RO);
	EXPECT_EQ((int )fro, FileMode::RO);
	EXPECT_EQ(fro.getMode(), FileMode::RO);
	EXPECT_STREQ(fro.getStringMode().c_str(), "------r--");

	FileMode fwo(FileMode::WO);
	EXPECT_EQ((int )fwo, FileMode::WO);
	EXPECT_EQ(fwo.getMode(), FileMode::WO);
	EXPECT_STREQ(fwo.getStringMode().c_str(), "-------w-");

	FileMode fxg(FileMode::XG);
	EXPECT_EQ((int )fxg, FileMode::XG);
	EXPECT_EQ(fxg.getMode(), FileMode::XG);
	EXPECT_STREQ(fxg.getStringMode().c_str(), "-----x---");

	FileMode frg(FileMode::RG);
	EXPECT_EQ((int )frg, FileMode::RG);
	EXPECT_EQ(frg.getMode(), FileMode::RG);
	EXPECT_STREQ(frg.getStringMode().c_str(), "---r-----");

	FileMode fwg(FileMode::WG);
	EXPECT_EQ((int )fwg, FileMode::WG);
	EXPECT_EQ(fwg.getMode(), FileMode::WG);
	EXPECT_STREQ(fwg.getStringMode().c_str(), "----w----");

	FileMode fxu(FileMode::XU);
	EXPECT_EQ((int )fxu, FileMode::XU);
	EXPECT_EQ(fxu.getMode(), FileMode::XU);
	EXPECT_STREQ(fxu.getStringMode().c_str(), "--x------");

	FileMode fru(FileMode::RU);
	EXPECT_EQ((int )fru, FileMode::RU);
	EXPECT_EQ(fru.getMode(), FileMode::RU);
	EXPECT_STREQ(fru.getStringMode().c_str(), "r--------");

	FileMode fwu(FileMode::WU);
	EXPECT_EQ((int )fwu, FileMode::WU);
	EXPECT_EQ(fwu.getMode(), FileMode::WU);
	EXPECT_STREQ(fwu.getStringMode().c_str(), "-w-------");

	FileMode fwN(FileMode::None);
	EXPECT_EQ((int )fwN, FileMode::None);
	EXPECT_EQ(fwN.getMode(), FileMode::None);
	EXPECT_STREQ(fwN.getStringMode().c_str(), "---------");

	int all = FileMode::WO | FileMode::RO | FileMode::XO | FileMode::WG
	| FileMode::RG | FileMode::XG | FileMode::WU | FileMode::RU
	| FileMode::XU;

	FileMode fwA(all);
	EXPECT_EQ((int )fwA, all);
	EXPECT_EQ(fwA.getMode(), all);
	EXPECT_STREQ(fwA.getStringMode().c_str(), "rwxrwxrwx");
}

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

}

int main(	int argc,
			char **argv)
{
testing::InitGoogleTest(&argc, argv);
return RUN_ALL_TESTS();
}
