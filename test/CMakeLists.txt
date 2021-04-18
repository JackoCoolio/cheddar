cmake_minimum_required(VERSION 3.9.2)
project(CheddarTest)
set(CMAKE_CXX_STANDARD 17)

set(SOURCE
    main.cpp
    src/move_test.cpp
    src/gen_test.cpp
)

include_directories(${CHEDDAR_HEADERS_DIR})

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
    cheddar_test
    ${SOURCE}
)
target_link_libraries(
    cheddar_test
    engine
    gtest
)

include(GoogleTest)
gtest_discover_tests(cheddar_test)

install(TARGETS cheddar_test DESTINATION ${CHEDDAR_INSTALL_BIN_DIR})
