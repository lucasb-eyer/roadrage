
# include the SFML specific macros
include(${PROJECT_SOURCE_DIR}/cmake/Macros.cmake)

# let CMake know about our additional libraries paths (on Windows)
if (WINDOWS)
    set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${PROJECT_SOURCE_DIR}/extlibs/headers")
    if(COMPILER_GCC)
        set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${PROJECT_SOURCE_DIR}/extlibs/libs-mingw")
    elseif(COMPILER_MSVC)
        set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${PROJECT_SOURCE_DIR}/extlibs/libs-msvc")
    endif()
endif()

# add the SFML sources path
include_directories(${PROJECT_SOURCE_DIR}/src)

# define the path of our additional CMake modules
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/Modules/")

# set the output directory for SFML libraries
set(LIBRARY_OUTPUT_PATH "${PROJECT_BINARY_DIR}/lib")

# define the export symbol
add_definitions(-DSFML_EXPORTS)

# add the modules subdirectories
add_subdirectory(System)
add_subdirectory(Window)
add_subdirectory(Network)
add_subdirectory(Graphics)
add_subdirectory(Audio)
if(WINDOWS)
    add_subdirectory(Main)
endif()
