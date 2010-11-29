cmake_minimum_required(VERSION 2.8)

# set a default build type if none was provided
# this has to be done before the project() instruction!
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

# project name
project(roadrage)

# all source files
set(SRC ${PROJECT_SOURCE_DIR}/RoadRage.cpp)

# find OpenGL and GLU
find_package(OpenGL REQUIRED)

# all include directories
include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/sfml2/include)

set(BUILD_SHARED_LIBS FALSE CACHE BOOL "TRUE to build SFML as shared libraries, FALSE to build it as static libraries")
add_subdirectory(${PROJECT_SOURCE_DIR}/sfml2)

# all libraries
set(LIBS sfml-window sfml-system ${OPENGL_LIBRARIES} Xrandr)

# define the window target
add_executable(roadrage ${SRC})
target_link_libraries(roadrage ${LIBS})
