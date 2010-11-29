cmake_minimum_required(VERSION 2.8)

# set a default build type if none was provided
# this has to be done before the project() instruction!
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

# project name
project(tinyxml)

# all source files
set(SRC ${PROJECT_SOURCE_DIR}/tinyxml.cpp
        ${PROJECT_SOURCE_DIR}/tinyxmlerror.cpp
        ${PROJECT_SOURCE_DIR}/tinyxmlparser.cpp
   )

add_definitions(-DTIXML_USE_STL=1)

# all include directories
include_directories(${PROJECT_SOURCE_DIR})

# define the window target
add_library(tinyxml STATIC ${SRC})
