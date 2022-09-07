cmake_minimum_required(VERSION 3.14)
project(CSocketLib VERSION 0.1.0)

set(PROJECT_SOURCES
    "./core.h"
    "./sockaddr.h"
    "./sockaddr_unix.cpp"
    "./sockaddr_win32.cpp"
    "./socket_utils_unix.cpp"
    "./socket_utils_win32.cpp"
    "./socket_base.h"
    "./socket_imp_unix.cpp"
    "./socket_imp_win32.cpp"
    "./error.h"
    "./error.cpp"
    "./CSocket.h"
    "./CSocket.cpp"
)

add_library(CSocketLib STATIC ${PROJECT_SOURCES})