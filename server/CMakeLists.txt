cmake_minimum_required(VERSION 2.6)
set(EXECUTABLE_NAME "server_rtype")
project(rtype_server)

#if (WIN32)
#	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
#	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
#endif()

if (CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE Debug)
endif ()

# Define sources and executable
include_directories(network)
include_directories(ecs)
file(GLOB source_files
        network/*.hpp
        network/*.cpp
        ecs/*.hpp
        )

add_executable(${EXECUTABLE_NAME} ${source_files})
