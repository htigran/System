/*
 * file_types.h
 *
 *  Created on: 30 Mar 2016
 *      Author: thovhann
 */

#ifndef PLATFORM_FILE_FILE_TYPES_H_
#define PLATFORM_FILE_FILE_TYPES_H_

#include <iostream>
using namespace std;

namespace platform {

/**
 * @brief Defines some constants used in File class
 */
class FileTypes
{
    public:
        /**
         * @brief Size format enumeration
         */
        enum SizeFormat
        {
            /** Byte representation **/
            Byte,
            /** Kilobyte representation **/
            Kbyte,
            /** Megabyte representation **/
            Mbyte,
            /** Gigabyte representation **/
            Gbyte,
            /** Terabyte representation **/
            Tbyte
        };

        enum SeekMode
        {
            /** Seek from the beginning of the file **/
            SeekBegin = 0,
            /** Seek from the current position **/
            SeekCurrent = 1,
            /** Seek from the end of the file **/
            SeekEnd  = 2
        };

        enum FilePermission
        {
            /** No file mode found **/
            None = -1,
            /** RWX mask for owner **/
            RWXU = 0000700,

            /** R mask for owner **/
            RU = 0000400,

            /** W mask for owner **/
            WU = 0000200,

            /** X mask for owner **/
            XU = 0000100,

            /** RWX mask for group **/
            RWXG = 0000070,

            /** R mask for group **/
            RG = 0000040,

            /** W mask for group **/
            WG = 0000020,

            /** X mask for group **/
            XG = 0000010,

            /** RWX mask for others **/
            RWXO = 0000007,

            /** R mask for others **/
            RO = 0000004,

            /** W mask for others **/
            WO = 0000002,

            /** X masks for others **/
            XO = 0000001,

            /**  Set user id on execution **/
            SUID = 0004000,

            /** Set group id on execution **/
            SGID = 0002000,

            /** Save swapped text even after use **/
            SVTX = 0001000
        };

        /**
         * @brief Open file in read mode
         */
        static const string Read ;

        /**
         * @brief Open file in write mode
         */
        static const string Write;

        /**
         * @brief Open the file in read write mode
         */
        static const string ReadWrite ;

        /**
         * @brief Open the file in read write append mode
         */
        static const string Append ;

        /**
         * @brief End of file marker
         */
        static const int Eof;

};

} /* namespace platform */

#endif /* PLATFORM_FILE_FILE_TYPES_H_ */
