cmake_minimum_required(VERSION 3.1)

project(parser)

set(CMAKE_BUILD_TYPE Debug)

add_compile_options(-std=c++11)

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost COMPONENTS regex) 
find_package(Threads REQUIRED)

message("Boost_LIBRARIES : " ${Boost_LIBRARIES})


if(Boost_FOUND)

	add_executable(
		parser
		main.cpp
		preprocessor.cpp
		analyser.cpp
		class_information_package.cpp
		c_and_k.cpp
	)

target_link_libraries(parser ${Boost_LIBRARIES} pthread)
endif()
