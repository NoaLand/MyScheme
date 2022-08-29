#include "preload_libs/preload_libs.h"

#include "token/token.h"
#include "core/interpreter.h"

int main() {
    std::istream& is{std::cin};
    std::ostream& os{std::cout};
    function_context context;
    Token_stream ts{is, os, &context};

    preload_libs(context);
    ts.get_ostream() << "Let's start!" << std::endl;
    interpreter{context, ts}.scheme();
}

