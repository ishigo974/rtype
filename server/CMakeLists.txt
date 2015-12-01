cmake_minimum_required(VERSION 3.2)
set(EXECUTABLE_NAME "server_rtype")
set(UT_NAME "server_ut")
project(rtype_server)

if (WIN32)
#	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
#	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
  set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "/W4 /WX -std=c++14")
endif()

if (UNIX)
  set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall -Werror -Wextra -std=c++14")
endif ()

if (CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE Debug)
endif ()

# Define sources and executable
include_directories(network)
include_directories(ecs)
include_directories(exceptions)
include_directories(base_ut)
include_directories(components)
include_directories(systems)
include_directories(classes)
include_directories(unit_tests)

file(GLOB source_files
        main.cpp
        ecs/*.hpp
      	ecs/*.cpp
        network/*.hpp
        network/*.cpp
        classes/*.hpp
        classes/*.cpp
        components/*.hpp
        components/*.cpp
        systems/*.hpp
        systems/*.cpp
      	exceptions/*.hpp
      	exceptions/*.cpp
      )

file(GLOB ut_source_files
        main_ut.cpp
        ecs/*.hpp
      	ecs/*.cpp
        network/*.hpp
        network/*.cpp
        classes/*.hpp
        classes/*.cpp
        components/*.hpp
        components/*.cpp
      	exceptions/*.hpp
      	exceptions/*.cpp
        systems/*.hpp
        systems/*.cpp
      	base_ut/*.hpp
        base_ut/*.cpp
        unit_tests/*.hpp
        unit_tests/*.cpp
      )

add_executable(${EXECUTABLE_NAME} ${source_files})
add_executable(${UT_NAME} ${ut_source_files})
