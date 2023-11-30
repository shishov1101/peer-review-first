cmake_minimum_required(VERSION 3.5)

project(peer-review-first LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(peer-review-first main.cpp)

install(TARGETS peer-review-first
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
