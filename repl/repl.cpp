#include "core/interpreter.h"

int main() {
    std::istream& is{std::cin};
    std::ostream& os{std::cout};
    function_context context;
    Token_stream ts{is, os, &context};

    ts.get_ostream() << "Let's start!" << std::endl;

    auto i = interpreter{context, ts};
    while(ts.get_istream()) {
        i.scheme();
    }
}

