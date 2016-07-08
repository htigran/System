# Stop if cmake version below 2.8
CMAKE_MINIMUM_REQUIRED(VERSION 2.8 FATAL_ERROR)

# Project name
PROJECT(SysProj C CXX)

IF(CMAKE_COMPILER_IS_GNUCXX)
    ADD_DEFINITIONS(-Wall -ansi -Wno-deprecated -pthread)
ENDIF()

# set the output paths
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
SET(BIN_INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin)
SET(DOC_INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin/doc)

# set build type to Debug if is not specified
IF(NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE "Debug" CACHE STRING "" FORCE)
ENDIF()

# automatically include the source and build directories in the include path
SET(CMAKE_INCLUDE_CURRENT_DIR ON)

MESSAGE(STATUS "Building ${PROJECT_NAME} in ${CMAKE_BUILD_TYPE} mode")

# enable unit tests
ENABLE_TESTING()

# emulate 'make check'
ADD_CUSTOM_TARGET(check COMMAND ${CMAKE_CTEST_COMMAND})

# enable @rpath in the install name for any shared library being built
SET(CMAKE_MACOSX_RPATH ON)

# Location of additional cmake modules
SET(CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH}
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake
  CACHE
  FORCE
  CMAKE_MODULE_PATH
)

ADD_SUBDIRECTORY(platform)

INCLUDE(CTest)
