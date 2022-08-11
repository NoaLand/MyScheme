#include "token/token.h"
#include "token/s_expression/atom.h"
#include "token/s_expression/list.h"
#include "token/function/list_family.h"
#include "token/function/s_expression_family.h"

std::istream& is{std::cin};
Token_stream ts{is};

void scheme(Token_stream& ts);
s_expression* construct_from_token(Token_stream& ts);
function* func(Token_stream& ts);
s_expression* closure(Token_stream& ts);

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
            case '(': {
                ts.put_back(token);
                s_expression* s_exp = closure(ts);
                s_exp->print(std::cout);
                continue;
            }
            case ')':
                continue;
            case 'F': {
                throw std::runtime_error("function **" + token.value + "** can only call in closure!");
            }
            default:
                std::cout << "others: " << token.value << std::endl;
                continue;
        }
    }
}

function* func(Token_stream& ts) {
    Token func = ts.get();
    std::string &function_key = func.value;
    function* f;
    if(function_key == "car") {
        s_expression* s_exp = closure(ts);
        f = new car{s_exp};
    } else if(function_key == "cdr") {
        s_expression* s_exp = closure(ts);
        f = new cdr{s_exp};
    } else if(function_key == "cons") {
        s_expression* left = construct_from_token(ts);
        s_expression* right = closure(ts);
        f = new cons{left, right};
    } else if(function_key == "null?") {
        s_expression* s_exp = closure(ts);
        f = new is_null{s_exp};
    } else if(function_key == "atom?") {
        s_expression* s_exp = construct_from_token(ts);
        f = new is_atom{s_exp};
    } else if(function_key == "eq?") {
        s_expression* left = construct_from_token(ts);
        s_expression* right = construct_from_token(ts);
        f = new is_eq{left, right};
    } else {
        throw std::runtime_error("unknown function: " + function_key);
    }

    const Token end = ts.get();
    if(end.type != ')') {
        throw std::runtime_error("wrong syntax: " + end.value);
    }

    return f;
}

s_expression* closure(Token_stream& ts) {
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
            list* pList = (list*) closure(ts);
            l->push_back(pList);
        } else if(token.type == 'F') {
            ts.put_back(token);
            return func(ts)->execute();
        } else {
            throw std::runtime_error("wrong syntax: " + token.value);
        }
    }

    return l;
}

s_expression* construct_from_token(Token_stream& ts) {
    Token token = ts.get();
    s_expression* s_exp;
    if(token.type == 'A') {
        s_exp = new atom{token.value};
    } else {
        ts.put_back(token);
        s_exp = closure(ts);
    }

    return s_exp;
}
