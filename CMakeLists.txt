cmake_minimum_required(VERSION 3.16)

project(rft VERSION 0.1 LANGUAGES C)

add_subdirectory(lib)
add_subdirectory(app)

configure_file(${PROJECT_SOURCE_DIR}/config.h.in ${PROJECT_SOURCE_DIR}/config.h)
