include(FetchContent)

FetchContent_Declare(googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.12.0)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(
        SchemeCoreTest
        s_expression/atom_test.cpp
        s_expression/params_test.cpp
        s_expression/list_test.cpp
        s_expression/function_declaration_test.cpp
        function/list_family_test.cpp
        function/math_family_test.cpp
        function/nor_logic_family_test.cpp
        function/others_test.cpp
        function/s_expression_family_test.cpp
        preload_libs/preload_libs_test.cpp
        token/token_test.cpp
        core/interpreter_test.cpp
)

target_link_libraries(
        SchemeCoreTest
        SchemeCore
        gtest_main
)
