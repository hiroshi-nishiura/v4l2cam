cmake_minimum_required (VERSION 3.5)
project(v4l2cam)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-fPIC")

file(GLOB SRCS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
add_library(${PROJECT_NAME} STATIC ${SRCS})

add_subdirectory(test_sdl)
#add_subdirectory(test_lua)
add_subdirectory(test_qt)
