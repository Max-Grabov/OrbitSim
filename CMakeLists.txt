cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

project(orbitsim)

target_include_directories(orbitsim INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/lib)

target_compile_definitions(orbitsim INTERFACE
    PROJECT_ROOT_DIR="${CMAKE_SOURCE_DIR}"
    PROJECT_BUILD_DIR="${CMAKE_SOURCE_DIR}/build")

add_executable(main.cpp orbitsim)
target_link_libraries(main.cpp PUBLIC orbitsim)