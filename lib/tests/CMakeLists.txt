if(RFT_BUILD_TESTS)

project(tests LANGUAGES CXX)
find_package(Boost COMPONENTS unit_test_framework REQUIRED)
enable_testing()

add_executable(${PROJECT_NAME}
    main.cpp
    test_cmplx.cpp
    test_touchstone.cpp
    )
target_link_libraries(${PROJECT_NAME} PRIVATE rft Boost::unit_test_framework)

endif()



add_executable(test test.c)
target_link_libraries(test PRIVATE rft)
