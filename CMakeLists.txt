cmake_minimum_required(VERSION 3.1)
project(fftsg LANGUAGES C CXX)

set(sources
    src/fftsg.c
    src/fftsg_float.c)

add_library(fftsg STATIC ${sources})

if(MSVC)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
endif()

target_compile_features(fftsg PRIVATE cxx_std_14)
if(MSVC)
    target_compile_options(fftsg PRIVATE /W4)
else()
    target_compile_options(fftsg PRIVATE -O2 -Wall)
endif()
target_include_directories(fftsg PUBLIC ${PROJECT_SOURCE_DIR}/include)

export(TARGETS fftsg FILE ${CMAKE_CURRENT_BINARY_DIR}/fftsgConfig.cmake)
