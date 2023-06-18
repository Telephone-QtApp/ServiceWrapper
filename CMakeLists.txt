cmake_minimum_required(VERSION 3.12)

project(service)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)
include_directories(include/Common)
include_directories(include/SystemSetting)

set(SOURCES
    src/main.cpp
    src/ServiceEngine.cpp
    src/SystemSetting/SystemSettingService.cpp
)

add_executable(service ${SOURCES})

target_link_libraries(service pthread)