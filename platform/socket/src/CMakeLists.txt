

add_library(Socket 
    socket.cpp
)


target_include_directories(Socket
    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR} # public include directories
)

target_link_libraries(Socket Dbg)
