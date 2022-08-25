include(FetchContent)

FetchContent_Declare(googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.10.x)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(
        SchemeCoreTest
        s_expression/atom_test.cpp
        s_expression/params_test.cpp)

target_link_libraries(
        SchemeCoreTest
        SchemeCore
        gtest_main
)
