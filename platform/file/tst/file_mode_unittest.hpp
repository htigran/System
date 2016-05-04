/*
 * file_mode.hpp
 *
 *  Created on: 29 Apr 2016
 *      Author: thovhann
 */

#ifndef PLATFORM_FILE_TST_FILE_MODE_UNITTEST_HPP_
#define PLATFORM_FILE_TST_FILE_MODE_UNITTEST_HPP_

#include <gtest/gtest.h>

namespace platformTest
{

using namespace platform;

//////////////////////////////////////////////////////
// FileMode
//////////////////////////////////////////////////////
TEST(FileMode, Int)
{
	FileMode::FileMode f(1);
	EXPECT_EQ((int )f, 1);
	EXPECT_EQ(f.getMode(), 1);
	EXPECT_STREQ(f.getStringMode().c_str(), "--------x");
}

TEST(FileMode, FilePermission)
{
	FileMode::FileMode fxo(FileMode::XO);
	EXPECT_EQ((int )fxo, FileMode::XO);
	EXPECT_EQ(fxo.getMode(), FileMode::XO);
	EXPECT_STREQ(fxo.getStringMode().c_str(), "--------x");

	FileMode::FileMode fro(FileMode::RO);
	EXPECT_EQ((int )fro, FileMode::RO);
	EXPECT_EQ(fro.getMode(), FileMode::RO);
	EXPECT_STREQ(fro.getStringMode().c_str(), "------r--");

	FileMode::FileMode fwo(FileMode::WO);
	EXPECT_EQ((int )fwo, FileMode::WO);
	EXPECT_EQ(fwo.getMode(), FileMode::WO);
	EXPECT_STREQ(fwo.getStringMode().c_str(), "-------w-");

	FileMode::FileMode fxg(FileMode::XG);
	EXPECT_EQ((int )fxg, FileMode::XG);
	EXPECT_EQ(fxg.getMode(), FileMode::XG);
	EXPECT_STREQ(fxg.getStringMode().c_str(), "-----x---");

	FileMode::FileMode frg(FileMode::RG);
	EXPECT_EQ((int )frg, FileMode::RG);
	EXPECT_EQ(frg.getMode(), FileMode::RG);
	EXPECT_STREQ(frg.getStringMode().c_str(), "---r-----");

	FileMode::FileMode fwg(FileMode::WG);
	EXPECT_EQ((int )fwg, FileMode::WG);
	EXPECT_EQ(fwg.getMode(), FileMode::WG);
	EXPECT_STREQ(fwg.getStringMode().c_str(), "----w----");

	FileMode::FileMode fxu(FileMode::XU);
	EXPECT_EQ((int )fxu, FileMode::XU);
	EXPECT_EQ(fxu.getMode(), FileMode::XU);
	EXPECT_STREQ(fxu.getStringMode().c_str(), "--x------");

	FileMode::FileMode fru(FileMode::RU);
	EXPECT_EQ((int )fru, FileMode::RU);
	EXPECT_EQ(fru.getMode(), FileMode::RU);
	EXPECT_STREQ(fru.getStringMode().c_str(), "r--------");

	FileMode::FileMode fwu(FileMode::WU);
	EXPECT_EQ((int )fwu, FileMode::WU);
	EXPECT_EQ(fwu.getMode(), FileMode::WU);
	EXPECT_STREQ(fwu.getStringMode().c_str(), "-w-------");

	FileMode::FileMode fwN(FileMode::None);
	EXPECT_EQ((int )fwN, FileMode::None);
	EXPECT_EQ(fwN.getMode(), FileMode::None);
	EXPECT_STREQ(fwN.getStringMode().c_str(), "---------");

	int all = FileMode::WO | FileMode::RO | FileMode::XO | FileMode::WG
	| FileMode::RG | FileMode::XG | FileMode::WU | FileMode::RU
	| FileMode::XU;

	FileMode::FileMode fwA(all);
	EXPECT_EQ((int )fwA, all);
	EXPECT_EQ(fwA.getMode(), all);
	EXPECT_STREQ(fwA.getStringMode().c_str(), "rwxrwxrwx");
}

}
 // namespace platform

#endif /* PLATFORM_FILE_TST_FILE_MODE_UNITTEST_HPP_ */
