cmake_minimum_required(VERSION 3.22)
project(MyScheme)

set(CMAKE_CXX_STANDARD 20)

add_executable(MyScheme
        src/scheme.cpp
        src/token/token.cpp
        src/token/s_expression/list.cpp
        src/token/s_expression/atom.cpp
        src/function/list_family.cpp
        src/function/s_expression_family.cpp
        src/token/s_expression/params.cpp
        src/token/s_expression/function_declaration.cpp
        src/function/nor_logic_family.cpp
        src/function/math_family.cpp
        src/function/others.cpp
)
