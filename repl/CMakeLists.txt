add_executable(repl repl.cpp ../include/core/function_context.h)
target_compile_features(repl PRIVATE cxx_std_20)

target_link_libraries(repl PRIVATE SchemeCore)