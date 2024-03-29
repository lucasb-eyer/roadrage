
# find doxygen
if(MACOSX)
    # Add some path to search doxygen in more directories.
    set(ADDITIONAL_PATHS 
        /Developer/Applications/Doxygen.app/Contents/Resources 
        /Developer/Applications/Doxygen.app/Contents/MacOS 
        $ENV{HOME}/Applications/Doxygen.app/Contents/Resources 
        $ENV{HOME}/Applications/Doxygen.app/Contents/MacOS 
        $ENV{HOME}/Applications/Developer/Doxygen.app/Contents/Resources 
        $ENV{HOME}/Applications/Developer/Doxygen.app/Contents/MacOS)
 
    set(CMAKE_PROGRAM_PATH ${CMAKE_PROGRAM_PATH} ${ADDITIONAL_PATHS})
endif()
find_package(Doxygen REQUIRED)

# set the input and output documentation paths
set(DOXYGEN_INPUT_DIR ${CMAKE_SOURCE_DIR})
set(DOXYGEN_OUTPUT_DIR ${CMAKE_BINARY_DIR}/doc)

# see if we can generate the CHM documentation
if(WINDOWS)
    # if HHC is found, we can generate the CHM (compressed HTML) output
    find_program(DOXYGEN_HHC_PROGRAM
                 NAMES hhc.exe
                 PATHS "c:/Program Files/HTML Help Workshop"
                 DOC "HTML Help Compiler program")
    if(DOXYGEN_HHC_PROGRAM)
        set(DOXYGEN_GENERATE_HTMLHELP YES)
    else()
        set(DOXYGEN_GENERATE_HTMLHELP NO)
    endif()
else()
    set(DOXYGEN_HHC_PROGRAM)
    set(DOXYGEN_GENERATE_HTMLHELP NO)
endif()

# configure the source Doxyfile by copying it and replacing all @variables@
set(DOXYGEN_CONFIGURED_INPUT ${DOXYGEN_OUTPUT_DIR}/doxyfile)
configure_file(${DOXYGEN_INPUT_DIR}/doc/doxyfile.in ${DOXYGEN_CONFIGURED_INPUT} @ONLY)

# copy the files needed by the documentation
configure_file(${DOXYGEN_INPUT_DIR}/doc/doxygen.css ${DOXYGEN_OUTPUT_DIR}/html/doxygen.css COPYONLY)
configure_file(${DOXYGEN_INPUT_DIR}/doc/logo.jpg    ${DOXYGEN_OUTPUT_DIR}/html/logo.jpg    COPYONLY)
configure_file(${DOXYGEN_INPUT_DIR}/doc/logo-bg.jpg ${DOXYGEN_OUTPUT_DIR}/html/logo-bg.jpg COPYONLY)

# target setup
add_custom_target(doc
                  COMMAND ${CMAKE_COMMAND} -E echo_append "Building API Documentation..."
                  COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_CONFIGURED_INPUT}
                  COMMAND ${CMAKE_COMMAND} -E echo "Done."
                  WORKING_DIRECTORY ${DOXYGEN_INPUT_DIR})

# setup install rules
install(DIRECTORY ${DOXYGEN_OUTPUT_DIR}/html
        DESTINATION ${INSTALL_MISC_DIR}/doc
        COMPONENT doc)
if(DOXYGEN_HHC_PROGRAM)
    install(FILES ${DOXYGEN_OUTPUT_DIR}/sfml.chm
            DESTINATION ${INSTALL_MISC_DIR}/doc
            COMPONENT doc)
endif()
