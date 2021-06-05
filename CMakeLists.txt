cmake_minimum_required(VERSION 3.10)

project(BlockchainCourse)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif()
 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

include_directories(source)

add_executable(BlockchainCourse source/main.cpp)
