cmake_minimum_required(VERSION 3.16)

project(rft VERSION 0.1 LANGUAGES C)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_STANDARD_REQUIRED On)
set(CMAKE_C_EXTENSIONS Off)

add_library(${PROJECT_NAME} STATIC
    rft_complex.c
    utils.c
    touchstone.c
    sparameters.c
    )
target_link_libraries(${PROJECT_NAME} PRIVATE -lm)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)

configure_file(${PROJECT_SOURCE_DIR}/config.h.in ${PROJECT_SOURCE_DIR}/config.h)

add_executable(rftools main.c)
target_link_libraries(rftools PRIVATE rft)
target_compile_options(rftools PRIVATE -Wall -Wextra -pedantic)






add_executable(test test.c)
target_link_libraries(test PRIVATE rft)
