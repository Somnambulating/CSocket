cmake_minimum_required(VERSION 3.0.0)
project("CSocket" VERSION 0.1.0)

# set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(PROJECT_SOURCES
)

if(APPLE)
    add_compile_options(
        -DDARWIN
        -DHAVE_SELECT
        -DHAVE_INET6
        -DHAVE_FIONBIO
        -DHAVE_UNIX_DOMAIN
    )
elseif(WIN32)
    add_compile_options(
        -DWINDOWS
        -DHAVE_SELECT
        -DHAVE_INET6
    )
elseif(UNIX)
    add_compile_options(
        -DLINUX
        -DHAVE_SELECT
        -DHAVE_INET6
        -DHAVE_UNIX_DOMAIN
    )
elseif(ANDROID)
    add_compile_options(
        -DLINUX
        -DHAVE_SELECT
        -DHAVE_INET6
        -DHAVE_UNIX_DOMAIN
    )
endif()