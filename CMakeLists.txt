cmake_minimum_required(VERSION 3.12)
project(captest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BINARY_DIR build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(TARGET_NAME captest)

add_subdirectory(src build)
add_executable(${TARGET_NAME} src/main.cpp)
target_link_libraries(${TARGET_NAME} PRIVATE libcaptest)