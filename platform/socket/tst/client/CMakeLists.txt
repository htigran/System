  
#Can manually add the sources using the set command as follows:
set(SOURCES main.cpp)
   
set(EXECUTABLE client_test)

add_executable(${EXECUTABLE} ${SOURCES})

target_link_libraries(${EXECUTABLE} socket)
