cmake_minimum_required(VERSION 3.2)
set(EXECUTABLE_NAME "rtype")
project(rtype_client)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/)
foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
    string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${PROJECT_SOURCE_DIR}/bin )
endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )

if (UNIX)
	set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall -Werror -Wextra -std=c++11")
endif()
if (WIN32)
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
	set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11")
endif ()

if (CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE Debug)
endif ()

# -------------------------- #
# Define include directories #
# -------------------------- #
include_directories(engine/core)
include_directories(engine/graphics)
include_directories(engine/network)

# -------------- #
# Define sources #
# -------------- #
file(GLOB source_files
        engine/core/*.cpp
        engine/core/*.hpp
        engine/graphics/*.cpp
        engine/graphics/*.hpp
        engine/network/*.cpp
        engine/network/*.hpp
        )

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
    set(SFML_ROOT "/usr")
endif ()

find_package(SFML 2 REQUIRED system window graphics network audio)

if (SFML_FOUND)
    message(STATUS ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
    include_directories(${SFML_INCLUDE_DIR})
endif ()

# ---- #
# Link #
# ---- #

add_executable(${EXECUTABLE_NAME} ${source_files})
target_link_libraries(${EXECUTABLE_NAME} ${SFML_DEPENDENCIES})
target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})