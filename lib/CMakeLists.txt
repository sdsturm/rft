project(rft C)

add_library(${PROJECT_NAME} STATIC
    rft_complex.c
    utils.c
    touchstone.c
    sparameters.c
    )
target_link_libraries(${PROJECT_NAME} PRIVATE -lm)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)

add_subdirectory(tests)
