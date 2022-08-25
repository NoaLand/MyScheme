add_executable(repl scheme.cpp)
target_compile_features(repl PRIVATE cxx_std_20)

target_link_libraries(repl PRIVATE SchemeCore)