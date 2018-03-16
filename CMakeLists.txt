cmake_minimum_required(VERSION 3.0)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "-std=c++11")

project(parser)

add_executable(
	parser
	main.cpp
	preprocessor.cpp
	analyser.cpp
)
