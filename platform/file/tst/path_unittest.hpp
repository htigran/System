/*
 * path_unittest.hpp
 *
 *  Created on: 29 Apr 2016
 *      Author: thovhann
 */

#ifndef PLATFORM_FILE_TST_PATH_UNITTEST_HPP_
#define PLATFORM_FILE_TST_PATH_UNITTEST_HPP_

#include <path.hpp>

#include <gtest/gtest.h>

using namespace platform;

#include <iostream>

namespace platformTest
{

TEST(PathTest, AbsolutePath)
{
	Path p("/root/parent/file.ext");
	EXPECT_STREQ(p.getAbsolutePath(), "/root/parent/file.ext");
	EXPECT_STREQ(p.getName().c_str(), "file.ext");
	EXPECT_STREQ(p.getParent().toString().c_str(), "/root/parent");
	EXPECT_STREQ(p.toString().c_str(), "/root/parent/file.ext");
	EXPECT_STREQ((const char*)p, "/root/parent/file.ext");
}

TEST(PathTest, RelativePath)
{
	Path p("../file.ext");
	Path ap = p.getAbsolutePath();
	EXPECT_STREQ(ap.getName().c_str(), "file.ext");
	EXPECT_EQ(ap[0], '/');
}

}

#endif /* PLATFORM_FILE_TST_PATH_UNITTEST_HPP_ */
