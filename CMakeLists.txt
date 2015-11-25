cmake_minimum_required(VERSION 3.2)
project(rtype)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall -Werror -Wextra -std=c++14")

add_subdirectory(client)