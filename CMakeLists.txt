cmake_minimum_required(VERSION 3.22)
project(
        MyScheme
        VERSION 1.0
        DESCRIPTION "My Scheme Compiler"
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)
add_subdirectory(repl)