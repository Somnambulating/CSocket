cmake_minimum_required(VERSION 3.14)
project(CSocketLib VERSION 0.1.0)

set(PROJECT_SOURCES
    "./core.h"
    "./socket.h"
    "./socket_imp_unix.cpp"
    "./socket_imp_win32.cpp"
    "./error.h"
    "./error.cpp"
    "./CSocket.h"
    "./CSocket.cpp"
)

add_library(CSocketLib STATIC ${PROJECT_SOURCES})