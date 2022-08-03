cmake_minimum_required(VERSION 3.22)
project(MyScheme)

set(CMAKE_CXX_STANDARD 20)

add_executable(MyScheme main.cpp token/token.cpp token/token.h token/scheme_list.cpp token/scheme_list.h)
