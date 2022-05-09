cmake_minimum_required(VERSION 3.21)
project(SimpleHash)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS -Wall)
set(SOURCE
        "Source/main.cpp;"
        "Source/SimpleHash.cpp;")
add_executable(${PROJECT_NAME} ${SOURCE})
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_LIST_DIR}/Include")