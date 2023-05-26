cmake_minimum_required(VERSION 3.26)

project(cbond)

add_subdirectory(lib/pttui lib/pttui/build)

include_directories(lib)

add_executable(
    ${PROJECT_NAME}
    src/cbond.c
)

target_link_libraries(${PROJECT_NAME} pttui cwalk)