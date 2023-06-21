cmake_minimum_required(VERSION 3.12)

project(service)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../Executable/Libraries)

include_directories(include)
include_directories(include/Common)
include_directories(include/SystemSetting)
include_directories(include/SmartPhone)

file(GLOB sources
    src/*.cpp
    src/*/*.cpp   
    src/*/*/*.cpp 
)

add_library(service SHARED ${sources})

add_compile_options(-pthread -ldl)

target_link_libraries(service dl ${GLIB_LIBRARIES})