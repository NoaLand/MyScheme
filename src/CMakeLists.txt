add_library(SchemeCore
        token/token.cpp
        s_expression/list.cpp
        s_expression/atom.cpp
        function/list_family.cpp
        function/s_expression_family.cpp
        s_expression/params.cpp
        s_expression/function_declaration.cpp
        function/nor_logic_family.cpp
        function/math_family.cpp
        function/others.cpp
        )

target_include_directories(SchemeCore PUBLIC ../include)
target_compile_features(SchemeCore PUBLIC cxx_std_20)