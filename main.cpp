#include "token/token.h"
#include "token/s_expression/atom.h"
#include "token/s_expression/list.h"
#include "token/function/list_family.h"
#include "token/function/s_expression_family.h"
#include "token/s_expression/params.h"
#include "token/s_expression/function_declaration.h"
#include "token/function/nor_logic_family.h"

std::istream& is{std::cin};
function_context context;
Token_stream ts{is, &context};

void scheme(Token_stream& ts);
function_declaration* function_define(Token_stream& ts);
s_expression* construct_from_token(Token_stream& ts);
s_expression* func(Token_stream& ts);
s_expression* closure(Token_stream& ts);
s_expression* get_input_param(Token_stream& ts);

void preload_libs();
void ignore_else(Token_stream& ts);

void preload_libs() {
    auto lat_params = new list();
    lat_params->push_back(new param{"l"});
    auto lat = new function_declaration(
            "lat?",
            lat_params,
            "(cond ( ( null? $l$ ) #t ) ( ( atom? ( car $l$ ) ) ( lat? ( cdr $l$ ) ) ) ( else #f ) )"
            );

    auto is_member_params = new list();
    is_member_params->push_back(new param{"a"});
    is_member_params->push_back(new param{"lat"});
    auto is_member = new function_declaration(
            "member?",
            is_member_params,
            "(cond ( ( null? $lat$ ) #f ) ( else ( or ( eq? ( car $lat$ ) $a$ ) ( member? $a$ ( cdr $lat$ ) ) ) ) ) "
            );

    auto rember_params = new list();
    rember_params->push_back(new param{"a"});
    rember_params->push_back(new param{"lat"});
    auto rember = new function_declaration(
            "rember",
            rember_params,
            "(cond ( ( null? $lat$ ) ( ( ) ) ) ( else ( cond ( ( eq? ( car $lat$ ) $a$ ) ( cdr $lat$ ) ) ( else ( cons ( car $lat$ ) ( rember $a$ ( cdr $lat$ ) ) ) ) ) ) ) "
            );

    context.store(lat);
    context.store(is_member);
    context.store(rember);
}

int main() {
    preload_libs();
    std::cout << "Let's start!" << std::endl;
    scheme(ts);
}

void scheme(Token_stream& ts) {
    while(ts.get_istream()) {
        Token token = ts.get();
        switch (token.type) {
            case 'A': {
                s_expression* s_exp;
                s_exp = new atom{token.value};
                s_exp->print(std::cout);
                continue;
            }
            case 'B': {
                s_expression* s_exp;
                s_exp = new boolean{token.value == "#t" || token.value == "else"};
                s_exp->print(std::cout);
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
            case 'D': {
                throw std::runtime_error("function definition can only inside closure!");
            }
            default:
                std::cout << "others: " << token.value << std::endl;
                continue;
        }
    }
}

s_expression* func(Token_stream& ts) {
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
    } else if(function_key == "or?") {
        s_expression* left = construct_from_token(ts);
        s_expression* right = construct_from_token(ts);
        f = new or_logic{left, right};
    } else if(function_key == "cond") {
        while(true) {
            Token condition_start = ts.get();
            if(condition_start.type == ')') {
                ts.get();
            }
            s_expression* assertion = construct_from_token(ts);
            if(assertion->get_indicator() != "bool") {
                throw std::runtime_error("wrong syntax! assertion need to return bool!");
            }
            if(((boolean*)assertion)->val()) {
                s_expression* res = construct_from_token(ts);
                ts.get();
                ignore_else(ts);
                return res;
            } else {
                ignore_else(ts);
            }
        }
    } else if(context.is_in(function_key)) {
        auto params = get_input_param(ts);
        std::string body = context.instantiate(params);
        ts.put_back(body);
        return closure(ts);
    } else {
        throw std::runtime_error("unknown function: " + function_key);
    }

    const Token end = ts.get();
    if(end.type != ')') {
        throw std::runtime_error("wrong syntax: " + end.value);
    }

    s_expression *pExpression = f->execute();
    std::cout << "-> " << f->name() << " -> " << f->return_type() << " [" << pExpression->get_value() << "]" << std::endl;
    return pExpression;
}

s_expression* get_input_param(Token_stream& ts) {
    list* params = new list();

    while(true) {
        const Token &token = ts.get();
        if(token.type != ')') {
            ts.put_back(token);
            const auto p = construct_from_token(ts);
            params->push_back(p);
        } else {
            break;
        }
    }

    return params;
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
            return func(ts);
        } else if(token.type == 'D') {
            ts.put_back(token);
            return function_define(ts);
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
    } else if(token.type == 'B') {
        s_exp = new boolean{token.value == "#t" || token.value == "else" };
    } else {
        ts.put_back(token);
        s_exp = closure(ts);
    }

    return s_exp;
}

s_expression* collect_params(Token_stream& ts);
std::string get_func_body(Token_stream& ts, s_expression* params);

function_declaration* function_define(Token_stream& ts) {
    Token define_keyword = ts.get();
    Token name = ts.get();
    if(name.type != 'A') {
        throw std::runtime_error("illegal func name!");
    }

    Token left_brackets = ts.get();

    Token lambda = ts.get();
    if(lambda.type != 'L') {
        throw std::runtime_error("wrong syntax in function define!");
    }

    s_expression* params = collect_params(ts);
    if(params->get_indicator() != "list") {
        throw std::runtime_error("wrong syntax in function define!");
    }

    std::string body = get_func_body(ts, params);

    auto* func = new function_declaration{name.value, params, body};
    context.store(func);
    return func;
}

s_expression* collect_params(Token_stream& ts) {
    const Token& left_bracket = ts.get();
    if(left_bracket.type != '(') {
        throw std::runtime_error("wrong syntax when declare parameters");
    }

    list* l = new list();
    while(true) {
        Token token = ts.get();
        if(token.type == 'A') {
            param* p = new param(token.value);
            l->push_back(p);
        } else if(token.type == ')') {
            break;
        } else {
            throw std::runtime_error("wrong syntax when declare parameters");
        }
    }

    return l;
}

std::string get_func_body(Token_stream& ts, s_expression* params) {
    const Token& left_bracket = ts.get();
    list* param_list = (list*)params;
    if(left_bracket.type != '(') {
        throw std::runtime_error("wrong syntax when declare function body");
    }
    int brackets = 1;

    std::string body;
    body += left_bracket.type;

    while(true) {
        Token token = ts.get();
        if(param_list->has_value(token.value)) {
            body += "$" + token.value + "$";
        } else {
            body += token.value;
        }

        if(token.type == '(') {
            body.push_back(token.type);
            ++brackets;
        } else if(token.type == ')') {
            body.push_back(token.type);
            --brackets;
        }

        body += " ";

        if(brackets == 0) {
            break;
        }
    }

    const Token& right_bracket = ts.get();
    if(right_bracket.type != ')') {
        throw std::runtime_error("wrong syntax when declare function body");
    }

    return body;
}

void ignore_else(Token_stream& ts) {
    int brackets = 1;
    while(true) {
        const Token &token = ts.get();
        if(token.type == '(') {
            ++brackets;
        } else if(token.type == ')') {
            --brackets;
        }

        if(brackets <= 0) {
            break;
        }
    }
}
