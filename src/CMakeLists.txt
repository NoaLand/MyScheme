add_library(SchemeCore
        core/token.cpp
        core/interpreter.cpp
        core/function/function_context.cpp
        s_expression/atom.cpp
        s_expression/params.cpp
        s_expression/function_declaration.cpp
        function/nor_logic_family.cpp
        function/math_family.cpp
        function/others.cpp
        function/list_family.cpp
        function/s_expression_family.cpp
        stream/token_stream.cpp
)

target_include_directories(SchemeCore PUBLIC ../include)
target_compile_features(SchemeCore PUBLIC cxx_std_20)