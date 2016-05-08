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
	File* m_fileStr;
	File* m_filePath;

	FileTest()
	{
		m_fileStr = new File("test_str.file");
		m_filePath = new File("test_path.file");
	}

	~FileTest()
	{
		::remove("test_str.file");
		::remove("test_path.file");
		delete m_fileStr;
		delete m_filePath;
	}
};

TEST_F(FileTest, notExist)
{
	// file should not exist at this point
	EXPECT_FALSE(m_fileStr->exists());
	EXPECT_FALSE(m_fileStr->isOpenned());
	EXPECT_FALSE(m_filePath->exists());
	EXPECT_FALSE(m_filePath->isOpenned());
	EXPECT_EQ(m_fileStr->getSize(), -1);
	EXPECT_EQ(m_filePath->getSize(), -1);
	EXPECT_FALSE(m_fileStr->isFile());
	EXPECT_FALSE(m_filePath->isFile());
}

TEST_F(FileTest, cantOpen)
{
	// file should not exist at this point so can't be opened
	EXPECT_EQ(m_fileStr->open(FileTypes::Read), -1);
	EXPECT_FALSE(m_fileStr->isOpenned());
	EXPECT_EQ(m_filePath->open(FileTypes::Read), -1);
	EXPECT_FALSE(m_filePath->isOpenned());
	EXPECT_EQ(m_fileStr->getSize(), -1);
	EXPECT_EQ(m_filePath->getSize(), -1);
	EXPECT_FALSE(m_fileStr->isFile());
	EXPECT_FALSE(m_filePath->isFile());
}

TEST_F(FileTest, Open)
{
	// file should not exist at this point so can't be opened
	EXPECT_EQ(m_fileStr->open(FileTypes::Write), 0);
	EXPECT_TRUE(m_fileStr->isOpenned());
	EXPECT_EQ(m_filePath->open(FileTypes::Write), 0);
	EXPECT_TRUE(m_filePath->isOpenned());
	EXPECT_EQ(m_fileStr->getSize(), 0);
	EXPECT_EQ(m_filePath->getSize(), 0);
	EXPECT_TRUE(m_fileStr->isFile());
	EXPECT_TRUE(m_filePath->isFile());
}

}
 // namespace platformTest

#endif /* PLATFORM_FILE_TST_FILE_UNITTEST_HPP_ */
