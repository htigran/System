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

namespace platformTest
{

struct PathTest : testing::Test
{
	Path* m_path;

	PathTest()
	{
		m_path = new Path("/root/parent/file.ext");
	}

	~PathTest()
	{
		delete m_path;
	}
};

TEST_F(PathTest, basic)
{
	EXPECT_STREQ(m_path->getAbsolutePath(), "/root/parent/file.ext");
	EXPECT_STREQ(m_path->getName().c_str(), "file.ext");
	EXPECT_STREQ(m_path->getParent().toString().c_str(), "parent");
	EXPECT_STREQ(m_path->toString().c_str(), "/root/parent/file.ext");
	EXPECT_STREQ((char*)m_path, "/root/parent/file.ext");
}

}

#endif /* PLATFORM_FILE_TST_PATH_UNITTEST_HPP_ */
