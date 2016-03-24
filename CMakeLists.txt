# CMakeLists files in this project can
# refer to the root source directory of the project as ${SYSTEMPROJECT_SOURCE_DIR} and
# to the root binary directory of the project as ${SYSTEMPROJECT_SOURCE_DIR}.
cmake_minimum_required (VERSION 2.8.0)
project (SystemProject)

# Recurse into the "platform" subdirectories. This does not actually
# cause another cmake executable to run. The same process will walk through
# the project's entire directory structure.
add_subdirectory (platform)
