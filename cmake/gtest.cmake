
FIND_PACKAGE(Threads REQUIRED)
FIND_PACKAGE(GTest QUIET)

if (NOT GTest_FOUND)
	set(GOOGLETEST_ROOT external/googletest/googletest)

    	set(GTEST_INCLUDE_DIRS 
		"${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/"
		"${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/include"
	)
    	INCLUDE_DIRECTORIES(PUBLIC ${GTEST_INCLUDE_DIRS})

	set(GOOGLETEST_SOURCES
	    ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/src/gtest-all.cc
	    ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/src/gtest_main.cc
	    )
	    
	foreach(_source ${GOOGLETEST_SOURCES})
	    set_source_files_properties(${_source} PROPERTIES GENERATED 1)
	endforeach()

	add_library(googletest ${GOOGLETEST_SOURCES})
	set(GTEST_BOTH_LIBRARIES googletest)
endif()
