cmake_minimum_required(VERSION 3.2)
set(EXECUTABLE_NAME "server_rtype")
set(UT_NAME "server_ut")
project(rtype_server)

if (WIN32)
    #	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
    #	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "/Wall /WX")
elseif (APPLE)
        set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall -Werror -Wextra -std=c++14")
elseif(UNIX)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall -Werror -Wextra -std=c++14 -pthread")
endif ()

if (CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE Debug)
endif ()

# Define sources and executable
if (WIN32)
    include_directories(network/Windows)
endif ()
if (UNIX)
include_directories(network/Unix)
endif ()
include_directories(network)
include_directories(base_ecs)
include_directories(exceptions)
include_directories(base_ut)
include_directories(components)
include_directories(systems)
include_directories(classes)
include_directories(commands)
include_directories(unit_tests)
include_directories(utils)

if (WIN32)
    file(GLOB network_files
    network/Windows/*.cpp)
endif ()
if (UNIX)
    file(GLOB network_files
            network/Unix/*.cpp)
endif ()

file(GLOB tmp
        client_protocol/*)

file(GLOB source_files
        main.cpp
        base_ecs/*.hpp
        base_ecs/*.cpp
        network/*.hpp
        network/*.cpp
        classes/*.hpp
        classes/*.cpp
        utils/*.hpp
        utils/*.cpp
        components/*.hpp
        components/*.cpp
        systems/*.hpp
        systems/*.cpp
        commands/*.hpp
        commands/*.cpp
        exceptions/*.hpp
        exceptions/*.cpp
        )

file(GLOB net_files
        main_network.cpp
        base_ecs/*.hpp
        base_ecs/*.cpp
        network/*.hpp
        network/*.cpp
        classes/*.hpp
        classes/*.cpp
        utils/*.hpp
        utils/*.cpp
        components/*.hpp
        components/*.cpp
        systems/*.hpp
        systems/*.cpp
        commands/*.hpp
        commands/*.cpp
        exceptions/*.hpp
        exceptions/*.cpp
        )

file(GLOB ut_source_files
        main_ut.cpp
        base_ecs/*.hpp
        base_ecs/*.cpp
        network/*.hpp
        network/*.cpp
        classes/*.hpp
        classes/*.cpp
        commands/*.hpp
        commands/*.cpp
        utils/*.hpp
        utils/*.cpp
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

add_executable(${EXECUTABLE_NAME} ${source_files} ${network_files} ${tmp})
add_executable(network_test ${net_files} ${network_files} ${tmp})
add_executable(${UT_NAME} ${ut_source_files} ${network_files} ${tmp})
