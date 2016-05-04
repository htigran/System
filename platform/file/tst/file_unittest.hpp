/*
 * file_unittest.hpp
 *
 *  Created on: 29 Apr 2016
 *      Author: thovhann
 */

#ifndef PLATFORM_FILE_TST_FILE_UNITTEST_HPP_
#define PLATFORM_FILE_TST_FILE_UNITTEST_HPP_

#include <file.hpp>

using namespace platform;

namespace platformTest
{

struct FileTest : testing::Test
{
	File* m_file;

	FileTest() {
		m_file = new File("test.file");
	}

	~FileTest() {
		delete m_file;
	}
};

TEST_F(FileTest, basic)
{
	// file should not exist at this point
	EXPECT_EQ(m_file->exists(), FALSE);

	EXPECT_EQ(m_file->isOpenned(), FALSE);
}

} // namespace platformTest

#endif /* PLATFORM_FILE_TST_FILE_UNITTEST_HPP_ */
