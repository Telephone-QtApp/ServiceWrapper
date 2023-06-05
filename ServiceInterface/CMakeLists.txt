cmake_minimum_required(VERSION 3.12)
project(srvinterface LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(COMMON_DIR ${CMAKE_CURRENT_SOURCE_DIR}/common)

include_directories(${COMMON_DIR})

add_executable(srvinterface main.cpp)