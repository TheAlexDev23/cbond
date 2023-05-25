cmake_minimum_required(VERSION 3.26)

project(cbond)

add_subdirectory(lib/pttui)
link_directories(lib/pttui/build)

add_executable(
    ${PROJECT_NAME}
    src/cbond.c
)

target_link_libraries(${PROJECT_NAME} pttui)