cmake_minimum_required (VERSION 3.5.1)
project (CharClient)

include_directories(include ../libutil/include)

SET(GCC_COVERAGE_COMPILE_FLAGS "-std=c++11 -Wall")
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

link_directories(/home/kunjan/Projects/ChatApp/libutil/build)

file(GLOB SOURCES "src/*.cpp")
add_executable(client ${SOURCES})
target_link_libraries(client pthread util)
 
