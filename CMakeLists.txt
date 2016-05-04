# Stop if cmake version below 2.8
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

# Project name
project(SysProj)

# Enable c, and c++ language
enable_language(C CXX)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Project version
SET(PROJECT_VERSION_MAJOR "0")
SET(PROJECT_VERSION_MINOR "1")
SET(PROJECT_VERSION_PATCH "0")
SET(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")
SET(PROJECT_VENDOR "TikoDza")
SET(PROJECT_COPYRIGHT_YEAR "2016")
SET(PROJECT_DOMAIN "tikodza")
  
# set the output paths
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

# set build type to Debug is not specified
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


# define project version (NOTE: replace with config.h.cmake ?)
ADD_DEFINITIONS(-DPROJECT_VERSION=\"${PROJECT_VERSION}\")

SET(BIN_INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin)
SET(DOC_INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin/doc)

# enable @rpath in the install name for any shared library being built
SET(CMAKE_MACOSX_RPATH ON)

# Location of additional cmake modules
set(CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH}
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake
  CACHE
  FORCE
  CMAKE_MODULE_PATH
)

add_subdirectory(platform)

enable_testing()
include(CTest)
