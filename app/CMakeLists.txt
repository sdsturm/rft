project(rftools C)

add_executable(${PROJECT_NAME}
    main.c
    main_utils.c
    crop.c
    td.c)

target_link_libraries(${PROJECT_NAME} PRIVATE rft)

target_compile_options(${PROJECT_NAME} PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
        -Wall -Wextra -Wconversion -pedantic-errors>
    $<$<CXX_COMPILER_ID:MSVC>:
          /WX /W4>)
