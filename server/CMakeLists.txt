cmake_minimum_required(VERSION 3.2)
set(EXECUTABLE_NAME "server_rtype")
set(UT_NAME "server_ut")
project(rtype_server)

if (WIN32)
    #	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
    #	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS}) #TODO FLAGS
elseif (APPLE)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall -Werror -Wextra -std=c++14")
elseif (UNIX)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-ldl -Wall -Werror -Wextra -std=c++14 -pthread")
endif ()

if (CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE Debug)
endif ()

# Define sources and executable
if (WIN32)
    include_directories(../common/network/Windows)
endif ()
if (UNIX)
    include_directories(../common/network/Unix)
endif ()
include_directories(../common/network)
include_directories(../common/exceptions)
include_directories(../common/utils)
include_directories(../common/classes)
include_directories(../common/mob_types)
include_directories(base_ecs)
include_directories(base_ut)
include_directories(exceptions)
include_directories(components)
include_directories(systems)
include_directories(classes)
include_directories(commands)
include_directories(unit_tests)
include_directories(utils)


if (WIN32)
    file(GLOB network_files
            ../common/network/Windows/*.cpp
            ../common/network/Windows/*.hpp)
endif ()

if (UNIX)
    file(GLOB network_files
            ../common/network/Unix/*.cpp
            ../common/network/Unix/*.hpp)
endif ()

file(GLOB source_files
        main.cpp
        base_ecs/*.hpp
        base_ecs/*.cpp
        ../common/network/*.hpp
        ../common/network/*.cpp
        ../common/classes/*.hpp
        ../common/classes/*.cpp
        classes/*.hpp
        classes/*.cpp
        exceptions/*.hpp
        exceptions/*.cpp
        utils/*.hpp
        utils/*.cpp
        components/*.hpp
        components/*.cpp
        systems/*.hpp
        systems/*.cpp
        commands/*.hpp
        commands/*.cpp
        ../common/exceptions/*.hpp
        ../common/exceptions/*.cpp
        ../common/utils/*.cpp
        ../common/utils/*.hpp
        )

file(GLOB ut_source_files
        main_ut.cpp
        base_ecs/*.hpp
        base_ecs/*.cpp
        ../common/network/*.hpp
        ../common/network/*.cpp
        ../common/classes/*.hpp
        ../common/classes/*.cpp
        exceptions/*.hpp
        exceptions/*.cpp
        classes/*.hpp
        classes/*.cpp
        commands/*.hpp
        commands/*.cpp
        utils/*.hpp
        utils/*.cpp
        components/*.hpp
        components/*.cpp
        ../common/exceptions/*.hpp
        ../common/exceptions/*.cpp
        systems/*.hpp
        systems/*.cpp
        base_ut/*.hpp
        base_ut/*.cpp
        unit_tests/*.hpp
        unit_tests/*.cpp
        ../common/utils/*.cpp
        ../common/utils/*.hpp
        )

add_executable(${EXECUTABLE_NAME} ${source_files} ${network_files})
add_executable(${UT_NAME} ${ut_source_files} ${network_files})

target_link_libraries(${EXECUTABLE_NAME} ${CMAKE_DL_LIBS})
target_link_libraries(${UT_NAME} ${CMAKE_DL_LIBS})
