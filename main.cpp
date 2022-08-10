#include "token/token.h"
#include "token/atom.h"
#include "token/list.h"

std::istream& is{std::cin};
Token_stream ts{is};

void scheme(Token_stream& ts);
s_expression * function(Token_stream& ts);
s_expression* handle_list(Token_stream& ts);

int main() {
    std::cout << "Let's start!" << std::endl;
    scheme(ts);
}

void scheme(Token_stream& ts) {
    while(ts.get_istream()) {
        Token token = ts.get();
        switch (token.type) {
            case 'A': {
                atom a{token.value};
                a.print(std::cout);
                continue;
            }
            case 'F': {
                ts.put_back(token);
                s_expression* res = function(ts);
                res->print(std::cout);
                continue;
            }
            case '(': {
                // actually, not only s_exp will start with (, almost everything in Scheme can be started with it, which means I need to match this with term
                // 1. s_exp
                ts.put_back(token);
                s_expression* s_exp = handle_list(ts);
                s_exp->print(std::cout);
                continue;
                // 2. other expression, so this version of code cannot run code like: car (car ((a))), since it will take (car ((a))) as list, but find `car` inside it
            }
            case ')':
                continue;
            default:
                std::cout << "others: " << token.value << std::endl;
                continue;
        }
    }
}

s_expression* function(Token_stream& ts) {
    Token func = ts.get();
    std::string &f = func.value;
    if(f == "car") {
        s_expression* l = handle_list(ts);
        if(l->get_indicator() != "list") {
            throw std::runtime_error("wrong syntax, car can only get list.");
        }
        s_expression* res = ((list*)l)->car();
        return res;
    } else {
        throw std::runtime_error("unknown function: " + f);
    }
}

s_expression* handle_list(Token_stream& ts) {
    const Token &left = ts.get();
    if(left.type != '(') {
        throw std::runtime_error("wrong syntax: " + left.value);
    }

    list* l = new list();
    while(true) {
        Token token = ts.get();
        if(token.type == 'A') {
            atom* a = new atom(token.value);
            l->push_back(a);
        } else if(token.type == ')') {
            break;
        } else if(token.type == '(') {
            ts.put_back(token);
            list* pList = (list*)handle_list(ts);
            l->push_back(pList);
        } else if(token.type == 'F') {
            ts.put_back(token);
            s_expression* res = function(ts);
            return res;
        } else {
            throw std::runtime_error("wrong syntax: " + token.value);
        }
    }

    return l;
}
