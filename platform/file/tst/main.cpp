/*
 * file_test.cpp
 *
 *  Created on: 28 Mar 2016
 *      Author: tigran
 */

#include <file.hpp>

// include tests
#include "file_mode_unittest.hpp"
#include "file_types_unittest.hpp"
#include "path_unittest.hpp"
#include "file_unittest.hpp"

#include <gtest/gtest.h>

int main(	int argc,
			char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
