project(rft C)

add_library(${PROJECT_NAME} SHARED
    cmplx.c
    utils.c
    touchstone.c
    nwparams.c
    sparams.c
    )

set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 90)
set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD_REQUIRED ON)

target_link_libraries(${PROJECT_NAME} PRIVATE -lm)

target_compile_options(${PROJECT_NAME} PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
        -Wall -Wextra -pedantic-errors>
    $<$<CXX_COMPILER_ID:MSVC>:
          /WX /W4>)

add_subdirectory(tests)
