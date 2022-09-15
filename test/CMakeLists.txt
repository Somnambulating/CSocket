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

set(HEADERS_DIRECTORY_PATH
    "../include"
)

set(SOURCES_DIRECTORY_PATH
    "../src"
)

set(HEADERS
    ${HEADERS_DIRECTORY_PATH}/core/core.h
    ${HEADERS_DIRECTORY_PATH}/core/error.h
    ${HEADERS_DIRECTORY_PATH}/event/event.h
    ${HEADERS_DIRECTORY_PATH}/socket/CSocket.h
    ${HEADERS_DIRECTORY_PATH}/socket/sockaddr.h
    ${HEADERS_DIRECTORY_PATH}/socket/socket_utils.h
    ${HEADERS_DIRECTORY_PATH}/socket/socket.h
)

set(SOURCES
    ${SOURCES_DIRECTORY_PATH}/core/error.cpp
    ${SOURCES_DIRECTORY_PATH}/socket/CSocket.cpp
    ${SOURCES_DIRECTORY_PATH}/socket/sockaddr_unix.cpp
    ${SOURCES_DIRECTORY_PATH}/socket/sockaddr_win32.cpp
    ${SOURCES_DIRECTORY_PATH}/socket/socket_imp_unix.cpp
    ${SOURCES_DIRECTORY_PATH}/socket/socket_imp_win32.cpp
    ${SOURCES_DIRECTORY_PATH}/socket/socket_utils_unix.cpp
    ${SOURCES_DIRECTORY_PATH}/socket/socket_utils_win32.cpp
)

add_executable(
  Test
  ${SOURCES}
  test.cpp
)
target_link_libraries(
  Test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(Test)