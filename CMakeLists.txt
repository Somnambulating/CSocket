cmake_minimum_required(VERSION 3.14)
project(CSocket VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)

if(APPLE)
    add_compile_options(
        -DUNIX
        -DHAVE_SELECT
        -DHAVE_INET6
        -DHAVE_FIONBIO
        -DHAVE_UNIX_DOMAIN
    )
elseif(WIN32)
    add_compile_options(
        -DWIN32
        -DHAVE_SELECT
        -DHAVE_INET6
    )
elseif(UNIX)
    add_compile_options(
        -DUNIX
        -DHAVE_SELECT
        -DHAVE_INET6
        -DHAVE_UNIX_DOMAIN
    )
endif()

add_subdirectory(src CSocketLib)
add_subdirectory(test Test)
add_subdirectory(demo Demo)