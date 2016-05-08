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

		Path p("test_path.file");
		m_filePath = new File(p);
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
	EXPECT_FALSE(m_filePath->exists());

	// file should not exist at this point so can't be opened for read
	EXPECT_EQ(m_fileStr->open(FileTypes::Read), -1);
	EXPECT_EQ(m_filePath->open(FileTypes::Read), -1);

	EXPECT_FALSE(m_fileStr->isOpenned());
	EXPECT_FALSE(m_filePath->isOpenned());

	EXPECT_EQ(m_fileStr->getSize(), -1);
	EXPECT_EQ(m_filePath->getSize(), -1);

	EXPECT_FALSE(m_fileStr->isFile());
	EXPECT_FALSE(m_filePath->isFile());

	EXPECT_TRUE(m_fileStr->eof());
	EXPECT_TRUE(m_filePath->eof());

	EXPECT_EQ(m_fileStr->writec('t'), -1);
	EXPECT_EQ(m_filePath->writec('t'), -1);

	EXPECT_EQ(m_fileStr->seek(0, FileTypes::SeekBegin), -1);
	EXPECT_EQ(m_filePath->seek(0, FileTypes::SeekBegin), -1);

	EXPECT_EQ(m_fileStr->readc(), FileTypes::Eof);
	EXPECT_EQ(m_filePath->readc(), FileTypes::Eof);

}

TEST_F(FileTest, OpenWriteOpenRead)
{
	EXPECT_EQ(m_fileStr->open(FileTypes::Write), 0);
	EXPECT_EQ(m_filePath->open(FileTypes::Write), 0);

	EXPECT_TRUE(m_fileStr->isOpenned());
	EXPECT_TRUE(m_filePath->isOpenned());

	EXPECT_EQ(m_fileStr->getSize(), 0);
	EXPECT_EQ(m_filePath->getSize(), 0);

	EXPECT_TRUE(m_fileStr->isFile());
	EXPECT_TRUE(m_filePath->isFile());

	EXPECT_FALSE(m_fileStr->eof());
	EXPECT_FALSE(m_filePath->eof());

	EXPECT_EQ(m_fileStr->writec('t'), 0);
	EXPECT_EQ(m_filePath->writec('t'), 0);

	EXPECT_EQ(m_fileStr->seek(0, FileTypes::SeekBegin), 0);
	EXPECT_EQ(m_filePath->seek(0, FileTypes::SeekBegin), 0);

	// EOF because file is open in write mode only
	EXPECT_EQ(m_fileStr->readc(), FileTypes::Eof);
	EXPECT_EQ(m_filePath->readc(), FileTypes::Eof);

	EXPECT_EQ(m_fileStr->flush(), 0);
	EXPECT_EQ(m_filePath->flush(), 0);

	EXPECT_EQ(m_fileStr->close(), 0);
	EXPECT_EQ(m_filePath->close(), 0);

	EXPECT_EQ(m_fileStr->remove(), 0);
	EXPECT_EQ(m_filePath->renameTo(*m_fileStr), 0);
	EXPECT_EQ(m_fileStr->renameTo(*m_filePath), 0);
	EXPECT_EQ(m_filePath->copyTo(*m_fileStr), 0);

	EXPECT_EQ(m_fileStr->open(FileTypes::Read), 0);
	EXPECT_EQ(m_filePath->open(FileTypes::Read), 0);

	EXPECT_EQ(m_fileStr->readc(), 't');
	EXPECT_EQ(m_filePath->readc(), 't');

	EXPECT_FALSE(m_fileStr->isDirectory());
	EXPECT_FALSE(m_filePath->isDirectory());

	FileMode f(0100744);
	EXPECT_EQ(m_fileStr->setMode(f), 0);
	EXPECT_EQ(m_filePath->setMode(f), 0);

	EXPECT_EQ(m_fileStr->getMode().getMode(), 0100744);
	EXPECT_EQ(m_filePath->getMode().getMode(), 0100744);

	// clean up
	EXPECT_EQ(m_fileStr->close(), 0);
	EXPECT_EQ(m_filePath->close(), 0);
}

TEST_F(FileTest, getHumanReadableSize)
{
	EXPECT_EQ(m_fileStr->open(FileTypes::Write), 0);
	EXPECT_FLOAT_EQ(m_fileStr->getHumanReadableSize(FileTypes::Byte), 0);
	EXPECT_FLOAT_EQ(m_fileStr->getHumanReadableSize(FileTypes::Kbyte), 0);
	EXPECT_FLOAT_EQ(m_fileStr->getHumanReadableSize(FileTypes::Mbyte), 0);
	EXPECT_FLOAT_EQ(m_fileStr->getHumanReadableSize(FileTypes::Gbyte), 0);
	EXPECT_FLOAT_EQ(m_fileStr->getHumanReadableSize(FileTypes::Tbyte), 0);
	for (int i = 0; i < 1024; ++i) {
		EXPECT_EQ(m_fileStr->writec('t'), 0);
	}
	EXPECT_EQ(m_fileStr->close(), 0);
	EXPECT_FLOAT_EQ(m_fileStr->getHumanReadableSize(FileTypes::Byte), 1024);
	EXPECT_FLOAT_EQ(m_fileStr->getHumanReadableSize(FileTypes::Kbyte), 1);
	EXPECT_FLOAT_EQ(m_fileStr->getHumanReadableSize(FileTypes::Mbyte), 0.0009746626);
	EXPECT_FLOAT_EQ(m_fileStr->getHumanReadableSize(FileTypes::Gbyte), 9.5142747e-07);
	EXPECT_FLOAT_EQ(m_fileStr->getHumanReadableSize(FileTypes::Tbyte), 9.1051594e-10);
}

TEST_F(FileTest, DirTest)
{
	{
		FileMode f(0100744);
		EXPECT_EQ(m_fileStr->mkdir(f), 0);
		EXPECT_EQ(m_fileStr->getMode().getMode(), 040744);
		EXPECT_EQ(m_fileStr->remove(), 0);
	}
	{
		FileMode f(0);
		EXPECT_EQ(m_fileStr->mkdir(f), 0);
		EXPECT_EQ(m_fileStr->getMode().getMode(), 040755);
		EXPECT_EQ(m_fileStr->remove(), 0);
	}

}

}
 // namespace platformTest

#endif /* PLATFORM_FILE_TST_FILE_UNITTEST_HPP_ */
