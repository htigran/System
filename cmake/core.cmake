
function(prepend var prefix)
   set(listVar "")
   foreach(f ${ARGN})
      list(APPEND listVar "${prefix}/${f}")
   endforeach(f)
   set(${var} "${listVar}" PARENT_SCOPE)
endfunction(prepend)

macro(add_modules)
    foreach(mod ${MODULES})
        
        #defaults
        set(SOURCE_FILES "")
        set(LIBS "")
        set(DEPENDENCIES "")
        
        # create lib
        include(${mod}/src/src.cmake)
        prepend(SOURCE_FILES ${mod}/src ${SOURCES})        
        add_library(${mod} SHARED
            ${SOURCE_FILES}
        )
        include_directories(PUBLIC ${mod}/inc)
        #add_dependencies(${mod} ${DEPENDENCIES})
        target_link_libraries(${mod} ${LIBS})
        
        add_subdirectory(${mod}/tst)
        
    endforeach(mod)
endmacro(add_modules)

####################################################

macro(addTest)
    INCLUDE_DIRECTORIES(PUBLIC ../inc ${GTEST_INCLUDE_DIRS})
    ADD_EXECUTABLE(${TEST_NAME} ${SOURCES})
    #ADD_DEPENDENCIES(${PROJECT_TEST_NAME} ${DEPENDENCIES})
    TARGET_LINK_LIBRARIES(${TEST_NAME}
        ${GTEST_BOTH_LIBRARIES}
        ${LIBS}
        )
    ADD_TEST(${TEST_NAME}_test  ${CMAKE_BINARY_DIR}/bin/${TEST_NAME})
endmacro(addTest)

add_modules()



