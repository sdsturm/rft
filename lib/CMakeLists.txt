project(rft C)

add_library(${PROJECT_NAME} STATIC
    cmplx.c
    utils.c
    touchstone.c
    sparameters.c
    )
    
target_link_libraries(${PROJECT_NAME} PRIVATE -lm)

target_compile_options(${PROJECT_NAME} PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
        -Wall -Wextra -Wconversion -pedantic-errors>
    $<$<CXX_COMPILER_ID:MSVC>:
          /WX /W4>)

add_subdirectory(tests)
