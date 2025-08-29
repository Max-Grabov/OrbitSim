cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

project(orbitsim)

file(GLOB SRC_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

find_library(SDL2 NAMES SDL PATHS "${CMAKE_CURRENT_SOURCE_DIR}/lib")

add_library(orbitsim STATIC ${SRC_FILES})

target_include_directories(orbitsim PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/lib)

target_compile_definitions(orbitsim PUBLIC
    PROJECT_ROOT_DIR="${CMAKE_SOURCE_DIR}"
    PROJECT_BUILD_DIR="${CMAKE_SOURCE_DIR}/build")

add_executable(orbitsim ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
 
target_link_libraries(orbitsim PRIVATE orbitsim)
target_link_libraries(orbitsim PRIVAYE SDL2)