#include "token/token.h"
#include "token/s_expression/atom.h"
#include "token/s_expression/list.h"
#include "token/function/list_family.h"
#include "token/function/s_expression_family.h"

std::istream& is{std::cin};
Token_stream ts{is};

void scheme(Token_stream& ts);
s_expression* function(Token_stream& ts);
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
            case 'F': {
                ts.put_back(token);
                s_expression* res = function(ts);
                res->print(std::cout);
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
        s_expression* s_exp = closure(ts);
        car c{s_exp};
        return c.execute();
    } else if(f == "cdr") {
        s_expression* s_exp = closure(ts);
        cdr c{s_exp};
        return c.execute();
    } else if(f == "cons") {
        s_expression* left;
        const Token &l_token = ts.get();
        if(l_token.type == 'A') {
            left = new atom{l_token.value};
        } else {
            ts.put_back(l_token);
            left = closure(ts);
        }

        s_expression* right = closure(ts);
        cons c{left, right};
        return c.execute();
    } else if(f == "null?") {
        s_expression* s_exp = closure(ts);
        is_null n{s_exp};
        return n.execute();
    }

    if(f == "atom?") {
        s_expression* s_exp;
        const Token &l_token = ts.get();
        if(l_token.type == 'A') {
            s_exp = new atom{l_token.value};
        } else {
            ts.put_back(l_token);
            s_exp = closure(ts);
        }

        is_atom a{s_exp};
        return a.execute();
    }

    throw std::runtime_error("unknown function: " + f);
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
            s_expression* res = function(ts);
            return res;
        } else {
            throw std::runtime_error("wrong syntax: " + token.value);
        }
    }

    return l;
}
