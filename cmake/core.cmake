
function(prepend var prefix)
   set(listVar "")
   foreach(f ${ARGN})
      list(APPEND listVar "${prefix}/${f}")
   endforeach(f)
   set(${var} "${listVar}" PARENT_SCOPE)
endfunction(prepend)

set(INCLUDE_DIRS /usr/local/include/)

macro(add_modules)

    # add libraries
    foreach(mod ${LIBRARIES})
        include(${mod}/src/src.cmake)
        prepend(SOURCE_FILES ${mod}/src ${SOURCES})        
        add_library(${mod} SHARED
            ${SOURCE_FILES}
        )
        target_include_directories(${mod} PUBLIC ${INCLUDE_DIRS})
        target_include_directories(${mod} PUBLIC  ${mod}/inc)
        target_link_libraries(${mod} ${DEPENDENCIES})
        add_subdirectory(${mod}/tst)
    endforeach(mod)
    
    # add applications
    foreach(mod ${APPLICATIONS})
        include(${mod}/src/src.cmake)
        prepend(SOURCE_FILES ${mod}/src ${SOURCES})        
        add_executable(${mod}
            ${SOURCE_FILES}
        )
        target_include_directories(${mod} PUBLIC ${INCLUDE_DIRS})
        target_include_directories(${mod} PUBLIC  ${mod}/inc)
        target_link_libraries(${mod} ${DEPENDENCIES})
        add_subdirectory(${mod}/tst)
    endforeach(mod)
    
endmacro(add_modules)

macro(addTest name sources)
    add_executable(${name} ${sources})
    ADD_TEST(${name}_c  ${CMAKE_BINARY_DIR}/bin/${name})
    target_include_directories(${name} PUBLIC  ../inc)
    add_dependencies(${name} googletest)
    TARGET_LINK_LIBRARIES(${name} googletest)
endmacro(addTest)

add_modules()



