#include "token/token.h"
#include "token/atom.h"
#include "token/list.h"

std::istream& is{std::cin};
Token_stream ts{is};

list handle_list(Token_stream ts);

int main() {
    std::cout << "Let's start!" << std::endl;

    while(ts.get_istream()) {
        Token token = ts.get();
        switch (token.type) {
            case 'A': {
                atom a{token.value};
                std::cout << a << std::endl;
                continue;
            }
            case '(': {
                // actually, not only l will start with (, almost everything in Scheme can be started with it, which means I need to match this with term
                // 1. l
                ts.put_back(token);
                list l = handle_list(ts);
                std::cout << l << std::endl;
                continue;
            }
            default:
                std::cout << "others: " << token.value << std::endl;
                continue;
        }
    }
}

list handle_list(Token_stream ts) {
    ts.get();
    list l;
    while(true) {
        Token token = ts.get();
        if(token.type == 'A') {
            atom* a = new atom(token.value);
            l.push_back(a);
        } else if(token.type == ')') {
            break;
        } else {
            throw std::runtime_error("wrong syntax: " + token.value);
        }
    }

    return l;
}
