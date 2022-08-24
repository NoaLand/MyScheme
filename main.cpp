#include <memory>

#include "token/token.h"
#include "token/s_expression/atom.h"
#include "token/s_expression/list.h"
#include "token/function/list_family.h"
#include "token/function/s_expression_family.h"
#include "token/s_expression/params.h"
#include "token/s_expression/function_declaration.h"
#include "token/function/nor_logic_family.h"
#include "token/function/math_family.h"
#include "token/function/others.h"

std::istream& is{std::cin};
auto context = std::make_shared<function_context>();
Token_stream ts{is, context};

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

    auto lat_length_params = new list();
    lat_length_params->push_back(new param{"lat"});
    auto lat_length = new function_declaration(
            "length",
            lat_length_params,
            "(cond ( ( null? $lat$ ) 0 ) ( else ( add1 ( length ( cdr $lat$ ) ) ) ) )"
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

    auto pick_params = new list();
    pick_params->push_back(new param{"n"});
    pick_params->push_back(new param{"lat"});
    auto pick = new function_declaration(
            "pick",
            pick_params,
            "(cond ( ( zero? ( sub1 $n$ ) ) ( car $lat$ ) ) ( else ( pick ( sub1 $n$ ) ( cdr $lat$ ) ) ) )"
            );

    auto rempick_params = new list();
    rempick_params->push_back(new param{"n"});
    rempick_params->push_back(new param{"lat"});
    auto rempick = new function_declaration(
            "rempick",
            rempick_params,
            "(cond ( ( zero? ( sub1 $n$ ) ) ( cdr $lat$ ) ) ( else ( cons ( car $lat$ ) ( rempick ( sub1 $n$ ) ( cdr $lat$ ) ) ) ) )"
            );

    auto add_params = new list();
    add_params->push_back(new param{"n"});
    add_params->push_back(new param{"m"});
    auto add = new function_declaration(
            "+",
            add_params,
            "(cond ( ( zero? $m$ ) $n$ ) ( else ( add1 ( + $n$ ( sub1 $m$ ) ) ) ) )"
            );

    auto sub_params = new list();
    sub_params->push_back(new param{"n"});
    sub_params->push_back(new param{"m"});
    auto sub = new function_declaration(
            "-",
            sub_params,
            "(cond ( ( zero? $m$ ) $n$ ) ( else ( sub1 ( - $n$ ( sub1 $m$ ) ) ) ) )"
            );

    auto multiplication_params = new list();
    multiplication_params->push_back(new param{"n"});
    multiplication_params->push_back(new param{"m"});
    auto multiplication = new function_declaration(
            "*",
            multiplication_params,
            "(cond ( ( zero? $m$ ) 0 ) ( else ( + $n$ ( * $n$ ( sub1 $m$ ) ) ) ) )"
            );

    auto divide_params = new list();
    divide_params->push_back(new param{"n"});
    divide_params->push_back(new param{"m"});
    auto divide = new function_declaration(
            "/",
            divide_params,
            "(cond ( ( < $n$ $m$ ) 0 ) ( else ( add1 ( / ( - $n$ $m$ ) $m$ ) ) ) )"
            );

    auto greater_than_params = new list();
    greater_than_params->push_back(new param{"n"});
    greater_than_params->push_back(new param{"m"});
    auto greater_than = new function_declaration(
            ">",
            greater_than_params,
            "(cond ( ( zero? $n$ ) #f ) ( ( zero? $m$ ) #t ) ( else ( > ( sub1 $n$ ) ( sub1 $m$ ) ) ) )"
            );

    auto less_than_params = new list();
    less_than_params->push_back(new param{"n"});
    less_than_params->push_back(new param{"m"});
    auto less_than = new function_declaration(
            "<",
            less_than_params,
            "(cond ( ( zero? $m$ ) #f ) ( ( zero? $n$ ) #t ) ( else ( < ( sub1 $n$ ) ( sub1 $m$ ) ) ) )"
            );

    auto equal_params = new list();
    equal_params->push_back(new param{"n"});
    equal_params->push_back(new param{"m"});
    auto equal = new function_declaration(
            "=",
            equal_params,
            "(cond ( ( > $n$ $m$ ) #f ) ( ( < $n$ $m$ ) #f ) ( else #t ) )"
            );

    auto expt_params = new list();
    expt_params->push_back(new param{"n"});
    expt_params->push_back(new param{"m"});
    auto expt = new function_declaration(
            "^",
            expt_params,
            "(cond ( ( zero? $m$ ) 1 ) ( else ( * $n$ ( ^ $n$ ( sub1 $m$ ) ) ) ) )"
            );

    context->store(lat);
    context->store(lat_length);
    context->store(is_member);
    context->store(rember);
    context->store(pick);
    context->store(rempick);
    context->store(add);
    context->store(sub);
    context->store(multiplication);
    context->store(divide);
    context->store(greater_than);
    context->store(less_than);
    context->store(equal);
    context->store(expt);
}

int main() {
    preload_libs();
    std::cout << "Let's start!" << std::endl;
    scheme(ts);
}

void scheme(Token_stream& ts) {
    while(ts.get_istream()) {
        std::cout << "> ";
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
            case 'N': {
                s_expression* s_exp;
                s_exp = new integer{token.integer_value};
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
    if(function_key == "quote") {
        auto any = ts.get();
        f = new quote{any};
    } else if(function_key == "car") {
        auto s_exp = closure(ts);
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
    } else if(function_key == "addtup") {
        s_expression* s_exp = construct_from_token(ts);
        f = new add_tuple{s_exp};
    } else if(function_key == "atom?") {
        s_expression* s_exp = construct_from_token(ts);
        f = new is_atom{s_exp};
    } else if(function_key == "eq?") {
        s_expression* left = construct_from_token(ts);
        s_expression* right = construct_from_token(ts);
        f = new is_eq{left, right};
    } else if(function_key == "number?") {
        s_expression* s_exp = construct_from_token(ts);
        f = new is_number{s_exp};
    } else if(function_key == "or?") {
        s_expression* left = construct_from_token(ts);
        s_expression* right = construct_from_token(ts);
        f = new or_logic{left, right};
    } else if(function_key == "and?") {
        s_expression* left = construct_from_token(ts);
        s_expression* right = construct_from_token(ts);
        f = new and_logic{left, right};
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
    } else if(function_key == "zero?") {
        s_expression* number = construct_from_token(ts);
        f = new is_zero{number};
    } else if(function_key == "add1") {
        s_expression* number = construct_from_token(ts);
        f = new self_add{number};
    } else if(function_key == "sub1") {
        s_expression* number = construct_from_token(ts);
        f = new self_sub{number};
    } else if(context->is_in(function_key, true)) {
        auto params = get_input_param(ts);
        std::string body = context->instantiate(params);
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
        } else if(token.type == 'B') {
            auto* b = new boolean(token.value == "#t" || token.value == "else");
            l->push_back(b);
        } else if(token.type == 'N') {
            auto* i = new integer(token.integer_value);
            l->push_back(i);
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
    } else if(token.type == 'N') {
        s_exp = new integer{ token.integer_value };
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
    context->store(func);
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

        if(token.type == 'N') {
            body += std::to_string(token.integer_value);
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
