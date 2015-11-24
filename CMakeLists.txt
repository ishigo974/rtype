cmake_minimum_required(VERSION 3.2)
project(rtype)

if (UNIX)
	set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall -Werror -Wextra -std=c++11")
endif()
if (WIN32)
		set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11")
endif()

add_subdirectory(client)