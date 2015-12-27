cmake_minimum_required(VERSION 3.2)
project(rtype_client)

# ------------#
# Basic setup #
# ------------#

set(EXECUTABLE_NAME "rtype")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BUILD_DIR}")

if (WIN32)
    foreach (OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
        string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${PROJECT_SOURCE_DIR}/../build/)
    endforeach (OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES)
endif ()

if (WIN32)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "/Wall /W4 -std=c++14")
endif ()

if (APPLE)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall -Wextra -Werror -std=c++14 -g3")
endif ()

if (UNIX)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-ldl -Wall -Wextra -Werror -std=c++14 -g3")
endif ()

# -------------- #
# Define sources #
# -------------- #

include_directories(lib)
include_directories(game)
include_directories(engine/core)
include_directories(engine/graphics)
include_directories(engine/network/client_protocol)
include_directories(../common/network)
include_directories(../common/exceptions)
include_directories(../common/mob_types)
include_directories(../common/classes)
include_directories(../common/utils)

if (WIN32)
    include_directories(../common/network/Windows)
endif ()
if (UNIX)
    include_directories(../common/network/Unix)
endif ()

file(GLOB source_files
        game/*.cpp
        engine/core/*.cpp
        engine/graphics/*.cpp
        engine/network/client_protocol/*.cpp
        ../common/network/*.cpp
        ../common/exceptions/*.cpp
        ../common/classes/*.cpp
        ../common/utils/*.cpp
        )

if (UNIX)
    file(GLOB net_files
            ../common/network/Unix/*.cpp)
endif ()

if (WIN32)
    file(GLOB net_files
            ../common/network/Windows/*.cpp)
endif ()

# ------------------- #
# Detect and add SFML #
# ------------------- #

if (WIN32)
    set(CMAKE_MODULE_PATH "C:\\SFML-2.3.2\\cmake\\Modules" ${CMAKE_MODULE_PATH})
    set(SFML_ROOT "C:\\SFML-2.3.2")
    set(SFML_STATIC_LIBRARIES TRUE)
endif ()

if (UNIX)
    set(CMAKE_MODULE_PATH "/usr/share/SFML/cmake/Modules/" ${CMAKE_MODULE_PATH})
    set(CMAKE_MODULE_PATH "/usr/local/share/SFML/cmake/Modules/" ${CMAKE_MODULE_PATH})
    set(SFML_ROOT "/usr/local")
endif ()

find_package(SFML 2 REQUIRED audio graphics window system)

# BOOST
if (UNIX)
    set(Boost_INCLUDE_DIR "/usr/local/include")
    set(Boost_LIBRARY_DIR "/usr/local/lib")
    set(Boost_INCLUDE_DIR "/usr/include")
    set(Boost_LIBRARY_DIR "/usr/lib")
endif ()

if (APPLE)
    set(Boost_INCLUDE_DIR "/usr/local/Cellar/boost/1.59.0/include")
    set(Boost_LIBRARY_DIR "/usr/local/Cellar/boost/1.59.0/lib")
endif ()

if (WIN32)
    set(BOOST_ROOT "C:/local/boost_1_59_0/")
    set(BOOST_INCLUDEDIR "C:/local/boost_1_59_0/boost")
    set(Boost_INCLUDE_DIR "C:/local/boost_1_59_0/")
    set(Boost_LIBRARY_DIR "C:/local/boost_1_59_0/lib32-msvc-14.0")
endif ()

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost REQUIRED)

if (SFML_FOUND)
    message(STATUS ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
    include_directories(${SFML_INCLUDE_DIR})
endif ()

if (Boost_FOUND)
    message(STATUS ${Boost_LIBRARIES} ${Boost_DEPENDENCIES})
    include_directories(${Boost_INCLUDE_DIR})
endif ()

# ---- #
# Link #
# ---- #

add_executable(${EXECUTABLE_NAME} ${source_files} ${net_files})

target_link_libraries(${EXECUTABLE_NAME} ${SFML_DEPENDENCIES})
target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
target_link_libraries(${EXECUTABLE_NAME} ${Boost_DEPENDENCIES})
target_link_libraries(${EXECUTABLE_NAME} ${Boost_LIBRARIES})
target_link_libraries(${EXECUTABLE_NAME} ${CMAKE_DL_LIBS})
