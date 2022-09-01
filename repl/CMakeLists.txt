add_executable(repl repl.cpp ../include/core/function/function_context.h ../include/stream/token_stream.h)
target_compile_features(repl PRIVATE cxx_std_20)

target_link_libraries(repl PRIVATE SchemeCore)