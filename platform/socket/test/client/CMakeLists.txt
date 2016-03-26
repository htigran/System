  
#Can manually add the sources using the set command as follows:
set(SOURCES main.cpp)
   
get_filename_component(EXECUTABLE ${CMAKE_CURRENT_SOURCE_DIR} NAME)

add_executable(${EXECUTABLE} ${SOURCES})

target_link_libraries(${EXECUTABLE} Socket)
