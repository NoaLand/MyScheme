cmake_minimum_required(VERSION 3.22)
project(MyScheme)

set(CMAKE_CXX_STANDARD 20)

add_executable(MyScheme
        scheme.cpp
        token/token.cpp
        token/s_expression/list.cpp
        token/s_expression/atom.cpp
        function/list_family.cpp
        function/s_expression_family.cpp
        token/s_expression/params.cpp
        token/s_expression/function_declaration.cpp
        function/nor_logic_family.cpp
        function/math_family.cpp
        function/others.cpp
        )
