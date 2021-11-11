cmake_minimum_required(VERSION 3.15)

#--------------------------------------------------------------------------------------------
# Initiate project
#--------------------------------------------------------------------------------------------

# Set the name of the main target
set(MAIN_TARGET BeorgTest)
# Initiate the project
project(${MAIN_TARGET} CXX)

# Include subdirectory with public definitions
include_directories(${PUBLIC_HEADERS_DIR})# Include subdirectory with public definitions
include_directories(${PUBLIC_SOURCES_DIR})

set(PUBLIC_HEADERS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(PUBLIC_SOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_17)

if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
    option(ENABLE_BUILD_WITH_TIME_TRACE "Enable -ftime-trace to generate time tracing .json files on clang" OFF)
    if(ENABLE_BUILD_WITH_TIME_TRACE)
        add_compile_definitions(project_options INTERFACE -ftime-trace)
    endif()
endif()

find_package(OpenCV 4.2 QUIET)
if(NOT OpenCV_FOUND)
    message(FATAL_ERROR "OpenCV > 4.2.0 not found.")
endif()

# Add the main target
add_subdirectory(src)

set_target_properties(${MAIN_TARGET} PROPERTIES LINKER_LANGUAGE CXX)