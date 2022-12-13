project(rftools C)

add_executable(rftools
    main.c
    main_utils.c
    crop.c
    td.c)

target_link_libraries(rftools PRIVATE rft)

target_compile_options(rftools PRIVATE -Wall -Wextra -pedantic)
