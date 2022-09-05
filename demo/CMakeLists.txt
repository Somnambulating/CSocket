cmake_minimum_required(VERSION 3.14)
project(Demo VERSION 0.1.0)

set(PROJECT_SOURCES
    "../src/darwin_config.h"
    "../src/linux_config.h"
    "../src/win_config.h"
    "../src/config.h"
    "../src/core.h"
    "../src/CSocket.h"
    "../src/CSocket.cpp"
)

# server
add_executable(
  server
  ${PROJECT_SOURCES}
  server.cpp
)

# client
add_executable(
  client
  ${PROJECT_SOURCES}
  client.cpp
)