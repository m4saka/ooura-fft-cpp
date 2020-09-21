cmake_minimum_required(VERSION 3.1)
project(fftsg LANGUAGES CXX)

set(sources
    ${PROJECT_SOURCE_DIR}/src/fftsg.c
    ${PROJECT_SOURCE_DIR}/src/fftsg_float.c)

# C++用のオーバーロードをコンパイルするためにcファイルをC++のソースとして扱う
set_source_files_properties(${sources} PROPERTIES LANGUAGE CXX)

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
