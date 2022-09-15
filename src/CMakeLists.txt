cmake_minimum_required(VERSION 3.14)
project(CSocketLib VERSION 0.1.0)

include_directories("../include")

set(HEADERS_DIRECTORY_PATH
    "../include"
)

set(HEADERS
    ${HEADERS_DIRECTORY_PATH}/core/core.h
    ${HEADERS_DIRECTORY_PATH}/core/error.h
    ${HEADERS_DIRECTORY_PATH}/event/event.h
    ${HEADERS_DIRECTORY_PATH}/socket/CSocket.h
    ${HEADERS_DIRECTORY_PATH}/socket/sockaddr.h
    ${HEADERS_DIRECTORY_PATH}/socket/socket_utils.h
    ${HEADERS_DIRECTORY_PATH}/socket/socket.h
    ${HEADERS_DIRECTORY_PATH}/tls/ssl_transport_security.h
    ${HEADERS_DIRECTORY_PATH}/event/event.h
)

set(SOURCES
    core/error.cpp
    socket/CSocket.cpp
    socket/sockaddr_unix.cpp
    socket/sockaddr_win32.cpp
    socket/socket_imp_unix.cpp
    socket/socket_imp_win32.cpp
    socket/socket_utils_unix.cpp
    socket/socket_utils_win32.cpp
    tls/ssl_transport_security.cpp
    event/event_engine_poll_unix.cpp
)

# openssl
find_package(OpenSSL REQUIRED)

add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES})

target_link_libraries(${PROJECT_NAME} OpenSSL::SSL OpenSSL::Crypto)