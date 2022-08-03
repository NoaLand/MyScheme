#include "token/token.h"

std::istream& is{std::cin};
Token_stream ts{is};

int main() {
    std::cout << "Let's start!" << std::endl;

    while(ts.get_istream()) {
        Token a = ts.get();
        if(a.type == 'A') {
            std::cout << "atom: " << a.value << std::endl;
        }
    }
}