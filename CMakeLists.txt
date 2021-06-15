cmake_minimum_required(VERSION 3.10)

project(Sylvestrupp)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif()
 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

include_directories(source)
include_directories(cryptopp)
include_directories(json)

file(GLOB CryptoPPSource
     "cryptopp/*.cpp"
)

add_library(CryptoPP ${CryptoPPSource})

add_subdirectory(source)

add_executable(Sylvestrupp source/main.cpp)
target_link_libraries(Sylvestrupp Core)
target_link_libraries(Sylvestrupp CryptoPP)
