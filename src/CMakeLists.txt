cmake_minimum_required(VERSION 3.15)

find_package(CUDA 10 REQUIRED)

file(GLOB ALL_PUBLIC_HEADERS 
    ${PUBLIC_HEADERS_DIR}/*.h)

source_group(TREE ${PUBLIC_HEADERS_DIR} 
    FILES 
    ${ALL_PUBLIC_HEADERS})

file(GLOB_RECURSE ALL_PRIVATE_SOURCES 
    *.cpp)

file(GLOB_RECURSE ALL_PRIVATE_HEADERS 
    *.h)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} 
    FILES 
    ${ALL_PRIVATE_HEADERS} 
    ${ALL_PRIVATE_SOURCES})
	
add_executable(${MAIN_TARGET}     
    ${ALL_PUBLIC_HEADERS}
    ${ALL_PRIVATE_HEADERS}
    ${ALL_PRIVATE_SOURCES})

target_include_directories(${MAIN_TARGET} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR})

# Link externals
target_link_libraries(${MAIN_TARGET} PRIVATE 
    CONAN_PKG::opencv
    CONAN_PKG::libzippp
    ${CUDA_npp_LIBRARY})

target_compile_options(${MAIN_TARGET} PRIVATE 
    ${CPPCORECHECK_COMPILE_OPTIONS})