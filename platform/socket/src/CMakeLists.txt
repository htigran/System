

add_library(Socket 
    socket.cpp
    socket_server.cpp
)


target_include_directories(Socket
    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR} # public include directories
)

target_link_libraries(Socket Dbg)
