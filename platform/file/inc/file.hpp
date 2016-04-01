//
//  file.hpp
//  Sockets
//
//  Created by Tigran Hovhannisyan on 19/03/2016.
//  Copyright © 2016 TIKO. All rights reserved.
//

#ifndef file_hpp
#define file_hpp

#include <file_mode.h>
#include <path.h>
#include <file_types.h>

#include  <stdio.h>
#include <sys/stat.h>
#include <dirent.h>

#include <iostream>
#include <vector>
using namespace std;

namespace platform
{

/**
 * @brief Allows operation on file
 */
class File : public FileTypes
{

public:

	/**
	 * @brief File class constructor. The file is not openned here, to open it you need to call the open() method
	 * @param p the string path to the file
	 * @see FileTypes
	 */
	File(const string& p);

	/**
	 * @brief File class constructor. The file is not openned here, to open it you need to call the open() method
	 * @param p the Path to the file
	 * @see FileTypes
	 */
	File(Path& p);

	/**
	 * @brief Opens the file in the defined mode
	 * @param mode the open mode
	 * @return 0 if success , -1 otherwise
	 */
	int open(const string& mode);

	/**
	 * @brief Tells whether the file exists or not
	 * @see FileTypes
	 * @return true if exists false otherwise
	 */
	bool exists();

	/**
	 * @brief Flushes the buffer
	 * @return 0 if success, -1 otherwise
	 */
	int flush();

	/**
	 * @brief removes the file
	 * @return 0 if success, -1 otherwise
	 */
	int remove();

	/**
	 * @brief closes the file
	 * @return 0 is success, -1 otherwise
	 */
	int close();

	/**
	 * @brief lists all the file in a dir
	 * @return vector<string> containing the file names
	 * 	an empty vector can menan that either there is no files in the directory or either that an error occured
	 */
	vector<string> getList();

	/**
	 * @brief return the Path object
	 * @return the Path object
	 */
	Path getPath();

	/**
	 * @brief get the file size
	 * @return the file size > 0 or -1 if error occured
	 */
	long getSize();

	/**
	 * @brief get a human readable representation of the size
	 * @param f FileTypes::SizeFormat
	 * @see FileTypes::SizeFormat
	 * @return the size in the good representation if success, -1 otherwise
	 */
	float getHumanReadableSize(FileTypes::SizeFormat f);

	/**
	 * @brief returns the mode of the file
	 * @return an int corresponfing to the mode
	 */
	FileMode getMode();

	/**
	 * @brief tells if the File is a file
	 * @return true if file false otherwise
	 */
	bool isFile();

	/**
	 * @brief tells if the File is a Folder
	 * @return true if folder, false otherwise
	 */
	bool isDirectory();

	/**
	 * @brief returns true is the file is openned false otherwise
	 * @return true or false
	 */
	bool isOpenned();

	/**
	 * @brief creates a directory with the current path with 0755 default mode
	 * @param m the file mode
	 * @return 0 is success, -1 otherwise
	 */
	int mkdir(FileMode m = FileTypes::RWXU);

	/**
	 * @brief sets the file mode
	 * @param mode the mode
	 * @returns 0 is success, -1 otherwise
	 */
	int setMode(FileMode& mode);

	/**
	 * @brief renames the file(move) to the target file. The target file must be non existent
	 * @param name the target File
	 * @return 0 if success, -1 otherwise
	 */
	int renameTo(File& name);

	/**
	 * @brief seeks the file from origin of offset size
	 * @return 0 is success, -1 otherwise
	 */
	int seek(	int offset,
				SeekMode origin);

	/**
	 * @brief Copies the file contents to another file. The target file will be overwritten if non empty
	 * @param to the target file
	 * @return 0 if success, -1 otherwise
	 */
	int copyTo(File& to);

	/**
	 * @brief reads the next char from the file
	 * @return the next char converted to int or FileTypes::ENDOFFILE
	 * @see FileTypes::ENDOFFILE
	 */
	int readc();

	/**
	 * @brief writes a char to the file
	 * @return 0 is SUCCESS, -1 otherwise
	 */
	int writec(char c);

	/**
	 * @brief checks is the EOF is reached
	 * @return true if EOF, false otherwise
	 */
	bool eof();

private:
	FILE* m_f;
	Path m_path;
	string m_mode;
	bool m_openned;
};

} /* namespace platform */

#endif // file_hpp
