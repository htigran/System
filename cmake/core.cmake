
function(prepend var prefix)
   set(listVar "")
   foreach(f ${ARGN})
      list(APPEND listVar "${prefix}/${f}")
   endforeach(f)
   set(${var} "${listVar}" PARENT_SCOPE)
endfunction(prepend)

macro(add_modules)
    foreach(mod ${MODULES})
        include(${mod}/src/src.cmake)
        prepend(SOURCE_FILES ${mod}/src ${SOURCES})        
        add_library(${mod} SHARED
            ${SOURCE_FILES}
        )
        target_include_directories(${mod} PUBLIC  ${mod}/inc)
        target_link_libraries(${mod} ${DEPENDENCIES})
        add_subdirectory(${mod}/tst)
    endforeach(mod)
endmacro(add_modules)

####################################################
## gtest
set(GOOGLETEST_ROOT external/googletest/googletest CACHE STRING "Google Test source root")

include_directories(
    ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}
    ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/include
    )
    
set(GOOGLETEST_SOURCES
    ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/src/gtest-all.cc
    ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/src/gtest_main.cc
    )
    
foreach(_source ${GOOGLETEST_SOURCES})
    set_source_files_properties(${_source} PROPERTIES GENERATED 1)
endforeach()

add_library(googletest ${GOOGLETEST_SOURCES})
####################################################

macro(addTest name sources)
    add_executable(${name} ${sources})
    ADD_TEST(${name}_c  ${CMAKE_BINARY_DIR}/bin/${name})
    target_include_directories(${name} PUBLIC  ../inc)
    add_dependencies(${name} googletest)
    TARGET_LINK_LIBRARIES(${name} googletest)
endmacro(addTest)

add_modules()



