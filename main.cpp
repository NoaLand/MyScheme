#include "token/token.h"
#include "token/scheme_list.h"

std::istream& is{std::cin};
Token_stream ts{is};

scheme_list handle_list(Token_stream ts);

int main() {
    std::cout << "Let's start!" << std::endl;

    while(ts.get_istream()) {
        Token a = ts.get();
        switch (a.type) {
            case 'A':
                std::cout << "atom: " << a.value << std::endl;
                continue;
            case '(': {
                // actually, not only list will start with (, almost everything in Scheme can be started with it, which means I need to match this with term
                // 1. list
                scheme_list l = handle_list(ts);
                std::cout << "list: " << l << std::endl;
                continue;
            }
            default:
                std::cout << "others: " << a.value << std::endl;
                continue;
        }
    }
}

scheme_list handle_list(Token_stream ts) {
    scheme_list l;
    while(true) {
        const Token &atom = ts.get();
        if(atom.type == 'A') {
            l.list.push_back(atom);
        } else if(atom.type == ')') {
            break;
        } else {
            throw std::runtime_error("wrong syntax: " + atom.value);
        }
    }

    return l;
}
