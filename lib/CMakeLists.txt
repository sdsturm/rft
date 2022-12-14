project(rft C CXX)

add_library(${PROJECT_NAME} SHARED
    cmplx.c
    utils.c
    touchstone.c
    nwparams.c
    sparams.c
    )

set(BLA_VENDOR OpenBLAS)
find_package(BLAS REQUIRED)
    
target_link_libraries(${PROJECT_NAME} PRIVATE -lm BLAS::BLAS)

target_compile_options(${PROJECT_NAME} PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
        -Wall -Wextra -pedantic-errors>
    $<$<CXX_COMPILER_ID:MSVC>:
          /WX /W4>)

add_subdirectory(tests)
