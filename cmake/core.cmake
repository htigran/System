
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
        include_directories(PUBLIC  ${mod}/inc)
        target_link_libraries(${mod} ${DEPENDENCIES})
        add_subdirectory(${mod}/tst)
    endforeach(mod)
endmacro(add_modules)

####################################################

macro(addTest name sources)
    add_executable(${name} ${sources})
    ADD_TEST(${name}_c  ${CMAKE_BINARY_DIR}/bin/${name})
    include_directories(PUBLIC  ../inc)
    TARGET_LINK_LIBRARIES(${name} ${mod} ${GTEST_LIBRARIES} ${DEPENDENCIES})
endmacro(addTest)

add_modules()



