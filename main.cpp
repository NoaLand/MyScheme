#include "token/token.h"
#include "token/atom.h"
#include "token/list.h"

std::istream& is{std::cin};
Token_stream ts{is};

list handle_list(Token_stream& ts);

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
            case 'F': {
                list l = handle_list(ts);
                const std::string &car = l.car();
                std::cout << "car of l: " << car << std::endl;
                continue;
            }
            case '(': {
                // actually, not only l will start with (, almost everything in Scheme can be started with it, which means I need to match this with term
                // 1. l
                ts.put_back(token);
                list l = handle_list(ts);
                std::cout << l << std::endl;
                continue;
                // 2. other expression, so this version of code cannot run code like: car (car ((a))), since it will take (car ((a))) as list, but find `car` inside it
            }
            default:
                std::cout << "others: " << token.value << std::endl;
                continue;
        }
    }
}

list handle_list(Token_stream& ts) {
    const Token &left = ts.get();
    if(left.type != '(') {
        throw std::runtime_error("wrong syntax: " + left.value);
    }

    list l;
    while(true) {
        Token token = ts.get();
        if(token.type == 'A') {
            atom* a = new atom(token.value);
            l.push_back(a);
        } else if(token.type == ')') {
            break;
        } else if(token.type == '(') {
            ts.put_back(token);
            list* pList = new list(handle_list(ts));
            l.push_back(pList);
        }  else {
            throw std::runtime_error("wrong syntax: " + token.value);
        }
    }

    return l;
}
