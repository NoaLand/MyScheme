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
        token/token_test.cpp
        core/interpreter_test.cpp
        runnable_the_little_schemer/atom_group/scheme_atom.cpp
        runnable_the_little_schemer/list_group/scheme_list.cpp
        runnable_the_little_schemer/list_group/list_family_group/scheme_list_function.cpp
        runnable_the_little_schemer/s_expression_family_group/scheme_s_expression_function.cpp
        runnable_the_little_schemer/customized_function_group/customized_function.cpp
        runnable_the_little_schemer/math_group/scheme_math.cpp runnable_the_little_schemer/sad_path/sad_path.cpp)

include_directories(./)
target_link_libraries(
        SchemeCoreTest
        SchemeCore
        gtest_main
        gmock_main
)
