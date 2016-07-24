cmake_minimum_required(VERSION 3.5.1)
project(Socket)
set(CMAKE_BUILD_TYPE Debug)
 
#Bring the headers, such as Student.h into the project
include_directories(include)
 
#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.cpp")
 
SET(GCC_COVERAGE_COMPILE_FLAGS "-std=c++11 -Wall")
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

#Generate the static library from the sources
add_library(util STATIC ${SOURCES})
