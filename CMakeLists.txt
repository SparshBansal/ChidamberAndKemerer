cmake_minimum_required(VERSION 3.1)

set(CMAKE_BUILD_TYPE Debug)
add_compile_options(-std=c++11)

project(parser)

add_executable(
	parser
	main.cpp
	preprocessor.cpp
	analyser.cpp
)
