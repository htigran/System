

add_library(Dbg 
    dbg.cpp
)


target_include_directories(Dbg
    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR} # public include directories
)
