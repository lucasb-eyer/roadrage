
set(INCROOT ${PROJECT_SOURCE_DIR}/include/SFML/Graphics)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/SFML/Graphics)

# all source files
set(SRC
    ${SRCROOT}/Arial.hpp
    ${SRCROOT}/Color.cpp
    ${INCROOT}/Color.hpp
    ${SRCROOT}/Drawable.cpp
    ${INCROOT}/Drawable.hpp
    ${SRCROOT}/Font.cpp
    ${INCROOT}/Font.hpp
    ${INCROOT}/Glyph.hpp
    ${SRCROOT}/GLCheck.cpp
    ${SRCROOT}/GLCheck.hpp
    ${SRCROOT}/Image.cpp
    ${INCROOT}/Image.hpp
    ${SRCROOT}/ImageLoader.cpp
    ${SRCROOT}/ImageLoader.hpp
    ${SRCROOT}/Matrix3.cpp
    ${INCROOT}/Matrix3.hpp
    ${INCROOT}/Matrix3.inl
    ${INCROOT}/Rect.hpp
    ${INCROOT}/Rect.inl
    ${SRCROOT}/Renderer.cpp
    ${INCROOT}/Renderer.hpp
    ${SRCROOT}/RenderImage.cpp
    ${INCROOT}/RenderImage.hpp
    ${SRCROOT}/RenderImageImpl.cpp
    ${SRCROOT}/RenderImageImpl.hpp
    ${SRCROOT}/RenderImageImplFBO.cpp
    ${SRCROOT}/RenderImageImplFBO.hpp
    ${SRCROOT}/RenderImageImplPBuffer.hpp
    ${SRCROOT}/RenderTarget.cpp
    ${INCROOT}/RenderTarget.hpp
    ${SRCROOT}/RenderWindow.cpp
    ${INCROOT}/RenderWindow.hpp
    ${SRCROOT}/Shader.cpp
    ${INCROOT}/Shader.hpp
    ${SRCROOT}/Shape.cpp
    ${INCROOT}/Shape.hpp
    ${SRCROOT}/Sprite.cpp
    ${INCROOT}/Sprite.hpp
    ${SRCROOT}/Text.cpp
    ${INCROOT}/Text.hpp
    ${SRCROOT}/View.cpp
    ${INCROOT}/View.hpp
    ${SRCROOT}/stb_image/stb_image.h
    ${SRCROOT}/stb_image/stb_image_write.h
)

# add platform specific sources
if(WINDOWS)
    set(SRC
        ${SRC}
        ${SRCROOT}/Win32/RenderImageImplPBuffer.cpp
        ${SRCROOT}/Win32/RenderImageImplPBuffer.hpp
    )
elseif(LINUX)
    set(SRC
        ${SRC}
        ${SRCROOT}/Linux/RenderImageImplPBuffer.cpp
        ${SRCROOT}/Linux/RenderImageImplPBuffer.hpp
    )
elseif(MACOSX)
    set(SRC
        ${SRC}
        ${SRCROOT}/OSX/RenderImageImplPBuffer.cpp
        ${SRCROOT}/OSX/RenderImageImplPBuffer.hpp
    )
endif()

# let CMake know about our additional graphics libraries paths (on Windows and OSX)
if (WINDOWS)
    set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${CMAKE_SOURCE_DIR}/extlibs/headers/freetype")
    set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${CMAKE_SOURCE_DIR}/extlibs/headers/GL")
    set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${CMAKE_SOURCE_DIR}/extlibs/headers/jpeg")

elseif (MACOSX)

    # Add freetype search path
    #set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${CMAKE_SOURCE_DIR}/extlibs/libs-osx/include/")
    set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${CMAKE_SOURCE_DIR}/extlibs/headers/freetype")
    set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${CMAKE_SOURCE_DIR}/extlibs/libs-osx/lib/")

    # Add GLEW search path
    #set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${CMAKE_SOURCE_DIR}/extlibs/libs-osx/include/")
    set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${CMAKE_SOURCE_DIR}/extlibs/headers/")
    set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${CMAKE_SOURCE_DIR}/extlibs/libs-osx/lib/")

    # Add jpeg search path
    #set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${CMAKE_SOURCE_DIR}/extlibs/libs-osx/include/jpeg")
    set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${CMAKE_SOURCE_DIR}/extlibs/headers/jpeg")
    set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${CMAKE_SOURCE_DIR}/extlibs/libs-osx/lib/")
endif()

# find external libraries
find_package(OpenGL REQUIRED)
find_package(Freetype REQUIRED)
find_package(GLEW REQUIRED)
find_package(JPEG REQUIRED)
if(LINUX)
    find_package(X11 REQUIRED)
endif()

# add include paths of external libraries
include_directories(${FREETYPE_INCLUDE_DIRS} ${GLEW_INCLUDE_PATH} ${JPEG_INCLUDE_DIR})

# build the list of libraries to link
# GL and X11 are only needed for shared build, as they are already linked by sfml-window
set(GRAPHICS_EXT_LIBS ${FREETYPE_LIBRARY} ${GLEW_LIBRARY} ${JPEG_LIBRARY})
if(BUILD_SHARED_LIBS)
    set(GRAPHICS_EXT_LIBS ${GRAPHICS_EXT_LIBS} ${OPENGL_gl_LIBRARY})
    if(LINUX)
        set(GRAPHICS_EXT_LIBS ${GRAPHICS_EXT_LIBS} ${X11_LIBRARIES})
    endif()
    if(MACOSX)
        # We use static version of freetype so we need to link against zlib.
        set(GRAPHICS_EXT_LIBS ${GRAPHICS_EXT_LIBS} z)
    endif()
endif()

# add preprocessor symbols
add_definitions(-DGLEW_STATIC -DSTBI_FAILURE_USERMSG)

# ImageLoader.cpp must be compiled with the -fno-strict-aliasing
# when gcc is used; otherwise saving PNGs may crash in stb_image_write
if(COMPILER_GCC)
    set_source_files_properties(${SRCROOT}/ImageLoader.cpp PROPERTIES COMPILE_FLAGS -fno-strict-aliasing)
endif()

# define the sfml-graphics target
sfml_add_library(sfml-graphics
                 SOURCES ${SRC}
                 DEPENDS sfml-window sfml-system
                 EXTERNAL_LIBS ${GRAPHICS_EXT_LIBS})
