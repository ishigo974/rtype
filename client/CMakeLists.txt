cmake_minimum_required(VERSION 3.2)
project(rtype_client)

# ------------#
# Basic setup #
# ------------#

set(EXECUTABLE_NAME "rtype")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/)
if (WIN32)
	foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
		string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
		set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${PROJECT_SOURCE_DIR}/bin )
	endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )
endif()

if (WIN32)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "/W4 /WX -std=c++14")
endif ()

if (UNIX)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall -Werror -Wextra -std=c++14")
endif ()

# -------------- #
# Define sources #
# -------------- #

include_directories(lib)
include_directories(engine/core)
include_directories(engine/graphics)

file(GLOB source_files
        engine/core/*.cpp
        engine/core/*.hpp
        engine/graphics/*.cpp
        engine/graphics/*.hpp
        engine/network/*.cpp
        engine/network/*.hpp
        lib/*.hpp
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
    set(SFML_ROOT "/usr/local")
endif ()

find_package(SFML 2 REQUIRED system window graphics network audio)
#find_package(Boost 1.59 REQUIRED)

if (SFML_FOUND)
    message(STATUS ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
    include_directories(${SFML_INCLUDE_DIR})
endif ()

#if (Boost_FOUND)
#    message(STATUS ${Boost_LIBRARIES} ${Boost_DEPENDENCIES})
#    include_directories(${Boost_INCLUDE_DIR})
#endif ()

# ---- #
# Link #
# ---- #

add_executable(${EXECUTABLE_NAME} ${source_files})

target_link_libraries(${EXECUTABLE_NAME} ${SFML_DEPENDENCIES})
target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
target_link_libraries(${EXECUTABLE_NAME} m)
#target_link_libraries(${EXECUTABLE_NAME} ${Boost_DEPENDENCIES})
#target_link_libraries(${EXECUTABLE_NAME} ${Boost_LIBRARIES})
