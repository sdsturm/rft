project(tests LANGUAGES C)

if(RFT_BUILD_TESTS)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)
enable_testing()
add_subdirectory(cmplx)
add_subdirectory(touchstone)

endif()





add_executable(test test.c)
target_link_libraries(test PRIVATE rft)
