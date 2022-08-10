cmake_minimum_required(VERSION 3.22)
project(MyScheme)

set(CMAKE_CXX_STANDARD 20)

add_executable(MyScheme
        main.cpp
        token/token.cpp
        token/s_expression/list.cpp
        token/s_expression/atom.cpp
        token/function/function.h
        token/function/list_family.cpp
        token/function/list_family.h
        token/function/s_expression_family.cpp token/function/s_expression_family.h)
