cmake_minimum_required(VERSION 3.14)
project(Demo VERSION 0.1.0)

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

# add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

# server
add_executable(
  server
  ${SOURCES}
  server.cpp
)

# client
add_executable(
  client
  ${SOURCES}
  client.cpp
)