cmake_minimum_required(VERSION 3.2)
project(rtype)

set(BUILD_DIR ${PROJECT_SOURCE_DIR}/build/ CACHE INTERNAL "output dir")

add_subdirectory(server)
add_subdirectory(client)
add_subdirectory(common/mob_types)