cmake_minimum_required(VERSION 3.14)
project(CSocketLib VERSION 0.1.0)

set(PROJECT_SOURCES
    "./darwin_config.h"
    "./linux_config.h"
    "./win_config.h"
    "./config.h"
    "./core.h"
    "./CSocket.h"
    "./CSocket.c"
)

add_library(CSocketLib STATIC ${PROJECT_SOURCES})