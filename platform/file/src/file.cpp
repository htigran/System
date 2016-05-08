//
//  file.cpp
//  Sockets
//
//  Created by Tigran Hovhannisyan on 19/03/2016.
//  Copyright © 2016 TIKO. All rights reserved.
//

#include <file.hpp>

namespace platform
{

File::File(Path& p)
		: 	m_f(NULL),
			m_path(p),
			m_openned(false)
{
}

File::File(const string& p)
		: 	m_f(NULL),
			m_path(p),
			m_openned(false)
{
}

int File::open(const string& mode)
{
	m_f = fopen(m_path, mode.c_str());

	if (m_f == NULL) {
		m_openned = false;
		return -1;
	}

	m_openned = true;
	return 0;
}

bool File::exists()
{
	FILE* file;
	file = fopen(m_path, "r");

	if (file != NULL) {
		fclose(file);
		return true;
	}

	return false;
}

int File::flush()
{
	return fflush(m_f);
}

int File::remove()
{
	return ::remove(m_path);
}

int File::close()
{
	if (isOpenned()) {
		m_openned = false;
		return fclose(m_f);
	}

	return 0;
}

long File::getSize()
{
	struct stat file_status;

	if (!this->exists())
		return -1;

	if (stat(m_path, &file_status) < 0) {
		return -1;
	}

	return file_status.st_size;
}

float File::getHumanReadableSize(SizeFormat f)
{
	long size = getSize();

	if (size < 0)
		return -1;

	switch (f) {
	case Byte:
		return size;

	case Kbyte:
		return float(size) / 1024;

	case Mbyte:
		return float(size) / 1050620;

	case Gbyte:
		return float(size) / 1076277500;

	case Tbyte:
		return float(size) / 1124637070400L;

	default:
		return -1;
	}
}

FileMode File::getMode()
{
	struct stat file_status;

	if (stat(m_path, &file_status) < 0) {
		return FileMode(FileTypes::None);
	}

	return FileMode(file_status.st_mode);
}

vector<string> File::getList()
{
	vector < string > vect;
	DIR* dir = opendir(m_path);
	struct dirent* ent;

	if (dir == NULL)
		return vect;

	while ((ent = readdir(dir)) != NULL) {
		string t;
		t = string(ent->d_name);

		if (t != "." && t != "..")
			vect.push_back(t);
	}

	return vect;
}

Path File::getPath()
{
	return m_path;
}

bool File::isFile()
{
	struct stat file_status;

	if (stat(m_path, &file_status) < 0) {
		return false;
	}

	if (file_status.st_mode & S_IFREG) {
		return true;
	}

	return false;
}

bool File::isDirectory()
{
	struct stat file_status;

	if (stat(m_path, &file_status) < 0) {
		return false;
	}

	if (file_status.st_mode & S_IFDIR) {
		return true;
	}

	return false;
}

bool File::isOpenned()
{
	return m_openned;
}

int File::mkdir(FileMode m)
{
	if (m == 0)
		return ::mkdir(m_path, 0755);

	else
		return ::mkdir(m_path, m);
}

int File::setMode(FileMode& mode)
{
	return chmod(m_path, mode);
}

int File::renameTo(File& f)
{
	if (f.exists() || !this->exists()) {
		return -1;
	}

	return rename(m_path, f.getPath());
}

int File::seek(	int offset,
				SeekMode origin)
{
	if (!isOpenned()) {
		return -1;
	}
	return fseek(m_f, offset, origin);
}

int File::copyTo(File& to)
{
	char ch;
	this->close();
	this->open(Read);
	to.close();
	to.open(Write);

	while (!this->eof()) {
		ch = this->readc();

		if (ch == -1) {
			this->close();
			to.close();
			return 0;
		}

		if (!to.eof())
			to.writec(ch);
	}

	if (this->close() < 0) {
		to.close();
		return -1;
	}

	if (to.close() < 0) {
		return -1;
	}

	return 0;
}

int File::readc()
{
	if (!isOpenned())
		return Eof;

	char c = fgetc(m_f);

	if (ferror (m_f)) {
		return Eof;
	}

	return c;
}

int File::writec(char c)
{
	if (!isOpenned())
		return -1;

	fputc(c, m_f);

	if (ferror (m_f)) {
		return Eof;
	}

	return 0;
}

bool File::eof()
{
	if (!isOpenned())
		return true;

	return feof(m_f);
}

} // namespace platform
