cmake_minimum_required(VERSION 3.2)
project(rtype_mobs)

# set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin )
# set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin/plugins )
# set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib )

# foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
#     string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
#     set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/../bin )
#     set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/../bin/plugins )
#     set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/../lib )
# endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${boostjsondb_SOURCE_DIR}/../../../bin/plugins)

set(FORWARDMOB "rtype_forwardmob")
set(VERTICALMOB "rtype_verticalmob")
set(SINUSOIDMOB "rtype_diagonalmob")

include_directories( ../utils )

file(GLOB forwardmob_files ForwardMobType.cpp ../utils/Utils.cpp)
file(GLOB verticalmob_files VerticalMobType.cpp ../utils/Utils.cpp)
file(GLOB diagonalmob_files DiagonalMobType.cpp ../utils/Utils.cpp)

add_library(${FORWARDMOB} MODULE ${forwardmob_files})
add_library(${VERTICALMOB} MODULE ${verticalmob_files})
add_library(${SINUSOIDMOB} MODULE ${diagonalmob_files})
