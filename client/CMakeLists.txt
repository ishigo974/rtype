cmake_minimum_required(VERSION 2.6)
set(EXECUTABLE_NAME "rtype")
project(rtype)

if (WIN32)
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "")
  set(CMAKE_BUILD_TYPE Debug)
endif()

# Define sources and executable
file (GLOB source_files
	core/*.cpp
)
add_executable(${EXECUTABLE_NAME} ${source_files})

# Detect and add SFML
if(WIN32)
	set(CMAKE_MODULE_PATH "C:\\SFML-2.3.2\\cmake\\Modules" ${CMAKE_MODULE_PATH})
	set(SFML_ROOT "C:\\SFML-2.3.2")
endif()
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
  message(STATUS ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_DEPENDENCIES})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()