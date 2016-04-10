/*
 * file_mode_test.cpp
 *
 *  Created on: 30 Mar 2016
 *      Author: thovhann
 */

#include <file_mode.h>

#include <gtest/gtest.h>

#include <iostream>

namespace platform
{

TEST(FileMode, Simple) {
	FileMode::FileMode f(1);
	EXPECT_EQ((int)f, 1);
	EXPECT_EQ(f.getMode(), 1);
	EXPECT_STREQ(f.getStringMode().c_str(), "--------x");
}

}
/* namespace platform */
