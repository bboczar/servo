project(Servo)

cmake_minimum_required(VERSION 3.8)

# Compilation flags
set(CMAKE_CXX_FLAGS "-std=c++20 ${CMAKE_CXX_FLAGS} -g -Wall -pedantic -Werror")

# Include dirs
include_directories(${PROJECT_SOURCE_DIR}/source)

# Build dir
set(CMAKE_BINARY_DIR "${PROJECT_SOURCE_DIR}/build")

# Subdirs
add_subdirectory(source)

# Deps
find_package(cpprestsdk REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} cpprest pthread ssl crypto)