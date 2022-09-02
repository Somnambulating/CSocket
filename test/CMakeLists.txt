cmake_minimum_required(VERSION 3.14)
project(Test VERSION 0.1.0)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  test
  test.cpp
)
target_link_libraries(
  test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(test)