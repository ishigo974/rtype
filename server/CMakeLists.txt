cmake_minimum_required(VERSION 3.2)
set(EXECUTABLE_NAME "server_rtype")
set(UT_NAME "server_ut")
project(rtype_server)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BUILD_DIR}")

if (WIN32)
    #	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
    #	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "/Wall -std=c++14") #TODO FLAGS
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
            ../common/network/Windows/*.cpp)
endif ()

if (UNIX)
    file(GLOB network_files
            ../common/network/Unix/*.cpp)
endif ()

file(GLOB source_files
        main.cpp
        base_ecs/*.cpp
        ../common/network/*.cpp
        ../common/classes/*.cpp
        classes/*.cpp
        exceptions/*.cpp
        utils/*.cpp
        components/*.cpp
        systems/*.cpp
        commands/*.cpp
        ../common/exceptions/*.cpp
        ../common/utils/*.cpp
        )

file(GLOB ut_source_files
        main_ut.cpp
        base_ecs/*.cpp
        ../common/network/*.cpp
        ../common/classes/*.cpp
        exceptions/*.cpp
        classes/*.cpp
        commands/*.cpp
        utils/*.cpp
        components/*.cpp
        ../common/exceptions/*.cpp
        systems/*.cpp
        base_ut/*.cpp
        unit_tests/*.cpp
        ../common/utils/*.cpp
        )

add_executable(${EXECUTABLE_NAME} ${source_files} ${network_files})
add_executable(${UT_NAME} ${ut_source_files} ${network_files})

target_link_libraries(${EXECUTABLE_NAME} ${CMAKE_DL_LIBS})
target_link_libraries(${UT_NAME} ${CMAKE_DL_LIBS})
