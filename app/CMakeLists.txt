project(rft-app C)

add_executable(${PROJECT_NAME}
    main.c
    main_utils.c
    crop.c
    td.c
    )

set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 90)
set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD_REQUIRED ON)

target_link_libraries(${PROJECT_NAME} PRIVATE rft)

target_compile_options(${PROJECT_NAME} PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
        -Wall -Wextra -pedantic-errors>
    $<$<CXX_COMPILER_ID:MSVC>:
          /WX /W4>)
