#include "preload_libs/preload_libs.h"

#include "token/token.h"
#include "core/interpreter.h"

int main() {
    std::istream& is{std::cin};
    function_context context;
    Token_stream ts{is, &context};

    preload_libs(context);
    std::cout << "Let's start!" << std::endl;
    interpreter{context, ts}.scheme();
}

