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
    auto lat_params = std::make_unique<list>();
    lat_params->push_back(std::move(std::make_unique<param>("l")));
    std::shared_ptr<function_declaration> lat(new function_declaration(
            "lat?",
            std::move(lat_params),
            "(cond ( ( null? $l$ ) #t ) ( ( atom? ( car $l$ ) ) ( lat? ( cdr $l$ ) ) ) ( else #f ) )"
            ));

    auto lat_length_params = std::make_unique<list>();
    lat_length_params->push_back(std::move(std::make_unique<param>("lat")));
    std::shared_ptr<function_declaration> lat_length(new function_declaration(
            "length",
            std::move(lat_length_params),
            "(cond ( ( null? $lat$ ) 0 ) ( else ( add1 ( length ( cdr $lat$ ) ) ) ) )"
            ));

    auto is_member_params = std::make_unique<list>();
    is_member_params->push_back(std::move(std::make_unique<param>("a")));
    is_member_params->push_back(std::move(std::make_unique<param>("lat")));
    std::shared_ptr<function_declaration> is_member(new function_declaration(
            "member?",
            std::move(is_member_params),
            "(cond ( ( null? $lat$ ) #f ) ( else ( or ( eq? ( car $lat$ ) $a$ ) ( member? $a$ ( cdr $lat$ ) ) ) ) ) "
            ));

    auto rember_params = std::make_unique<list>();
    rember_params->push_back(std::move(std::make_unique<param>("a")));
    rember_params->push_back(std::move(std::make_unique<param>("lat")));
    std::shared_ptr<function_declaration> rember(new function_declaration(
            "rember",
            std::move(rember_params),
            "(cond ( ( null? $lat$ ) ( ( ) ) ) ( else ( cond ( ( eq? ( car $lat$ ) $a$ ) ( cdr $lat$ ) ) ( else ( cons ( car $lat$ ) ( rember $a$ ( cdr $lat$ ) ) ) ) ) ) ) "
            ));

    auto pick_params = std::make_unique<list>();
    pick_params->push_back(std::move(std::make_unique<param>("n")));
    pick_params->push_back(std::move(std::make_unique<param>("lat")));
    std::shared_ptr<function_declaration> pick(new function_declaration(
            "pick",
            std::move(pick_params),
            "(cond ( ( zero? ( sub1 $n$ ) ) ( car $lat$ ) ) ( else ( pick ( sub1 $n$ ) ( cdr $lat$ ) ) ) )"
            ));

    auto rempick_params = std::make_unique<list>();
    rempick_params->push_back(std::move(std::make_unique<param>("n")));
    rempick_params->push_back(std::move(std::make_unique<param>("lat")));
    std::shared_ptr<function_declaration> rempick(new function_declaration(
            "rempick",
            std::move(rempick_params),
            "(cond ( ( zero? ( sub1 $n$ ) ) ( cdr $lat$ ) ) ( else ( cons ( car $lat$ ) ( rempick ( sub1 $n$ ) ( cdr $lat$ ) ) ) ) )"
            ));

    auto add_params = std::make_unique<list>();
    add_params->push_back(std::move(std::make_unique<param>("n")));
    add_params->push_back(std::move(std::make_unique<param>("m")));
    std::shared_ptr<function_declaration> add(new function_declaration(
            "+",
            std::move(add_params),
            "(cond ( ( zero? $m$ ) $n$ ) ( else ( add1 ( + $n$ ( sub1 $m$ ) ) ) ) )"
            ));

    auto sub_params = std::make_unique<list>();
    sub_params->push_back(std::move(std::make_unique<param>("n")));
    sub_params->push_back(std::move(std::make_unique<param>("m")));
    std::shared_ptr<function_declaration> sub(new function_declaration(
            "-",
            std::move(sub_params),
            "(cond ( ( zero? $m$ ) $n$ ) ( else ( sub1 ( - $n$ ( sub1 $m$ ) ) ) ) )"
            ));

    auto multiplication_params = std::make_unique<list>();
    multiplication_params->push_back(std::move(std::make_unique<param>("n")));
    multiplication_params->push_back(std::move(std::make_unique<param>("m")));
    std::shared_ptr<function_declaration> multiplication(new function_declaration(
            "*",
            std::move(multiplication_params),
            "(cond ( ( zero? $m$ ) 0 ) ( else ( + $n$ ( * $n$ ( sub1 $m$ ) ) ) ) )"
            ));

    auto divide_params = std::make_unique<list>();
    divide_params->push_back(std::move(std::make_unique<param>("n")));
    divide_params->push_back(std::move(std::make_unique<param>("m")));
    std::shared_ptr<function_declaration> divide(new function_declaration(
            "/",
            std::move(divide_params),
            "(cond ( ( < $n$ $m$ ) 0 ) ( else ( add1 ( / ( - $n$ $m$ ) $m$ ) ) ) )"
            ));

    auto greater_than_params = std::make_unique<list>();
    greater_than_params->push_back(std::move(std::make_unique<param>("n")));
    greater_than_params->push_back(std::move(std::make_unique<param>("m")));
    std::shared_ptr<function_declaration> greater_than(new function_declaration(
            ">",
            std::move(greater_than_params),
            "(cond ( ( zero? $n$ ) #f ) ( ( zero? $m$ ) #t ) ( else ( > ( sub1 $n$ ) ( sub1 $m$ ) ) ) )"
            ));

    auto less_than_params = std::make_unique<list>();
    less_than_params->push_back(std::move(std::make_unique<param>("n")));
    less_than_params->push_back(std::move(std::make_unique<param>("m")));
    std::shared_ptr<function_declaration> less_than(new function_declaration(
            "<",
            std::move(less_than_params),
            "(cond ( ( zero? $m$ ) #f ) ( ( zero? $n$ ) #t ) ( else ( < ( sub1 $n$ ) ( sub1 $m$ ) ) ) )"
            ));

    auto equal_params = std::make_unique<list>();
    equal_params->push_back(std::move(std::make_unique<param>("n")));
    equal_params->push_back(std::move(std::make_unique<param>("m")));
    std::shared_ptr<function_declaration> equal(new function_declaration(
            "=",
            std::move(equal_params),
            "(cond ( ( > $n$ $m$ ) #f ) ( ( < $n$ $m$ ) #f ) ( else #t ) )"
            ));

    auto expt_params = std::make_unique<list>();
    expt_params->push_back(std::move(std::make_unique<param>("n")));
    expt_params->push_back(std::move(std::make_unique<param>("m")));
    std::shared_ptr<function_declaration> expt(new function_declaration(
            "^",
            std::move(expt_params),
            "(cond ( ( zero? $m$ ) 1 ) ( else ( * $n$ ( ^ $n$ ( sub1 $m$ ) ) ) ) )"
            ));

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
                std::unique_ptr<s_expression> s_exp(new atom{token.value});
                s_exp->print(std::cout);
                continue;
            }
            case 'B': {
                std::unique_ptr<s_expression> s_exp(new boolean{token.value == "#t" || token.value == "else"});
                s_exp->print(std::cout);
                continue;
            }
            case 'N': {
                std::unique_ptr<s_expression> s_exp(new integer{token.integer_value});
                s_exp->print(std::cout);
                continue;
            }
            case '(': {
                ts.put_back(token);
                std::unique_ptr<s_expression> s_exp(closure(ts));
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
        auto s_exp = closure(ts);
        f = new cdr{s_exp};
    } else if(function_key == "cons") {
        auto left = construct_from_token(ts);
        auto right = closure(ts);
        f = new cons{left, right};
    } else if(function_key == "null?") {
        auto s_exp = closure(ts);
        f = new is_null{s_exp};
    } else if(function_key == "addtup") {
        auto s_exp = construct_from_token(ts);
        f = new add_tuple{s_exp};
    } else if(function_key == "atom?") {
        auto s_exp = construct_from_token(ts);
        f = new is_atom{s_exp};
    } else if(function_key == "eq?") {
        auto left = construct_from_token(ts);
        auto right = construct_from_token(ts);
        f = new is_eq{left, right};
    } else if(function_key == "number?") {
        auto s_exp = construct_from_token(ts);
        f = new is_number{s_exp};
    } else if(function_key == "or?") {
        auto left = construct_from_token(ts);
        auto right = construct_from_token(ts);
        f = new or_logic{left, right};
    } else if(function_key == "and?") {
        auto left = construct_from_token(ts);
        auto right = construct_from_token(ts);
        f = new and_logic{left, right};
    } else if(function_key == "cond") {
        while(true) {
            Token condition_start = ts.get();
            if(condition_start.type == ')') {
                ts.get();
            }
            auto assertion = construct_from_token(ts);
            if(assertion->get_indicator() != "bool") {
                throw std::runtime_error("wrong syntax! assertion need to return bool!");
            }
            if(((boolean*)assertion)->val()) {
                auto res = construct_from_token(ts);
                ts.get();
                ignore_else(ts);
                return res;
            } else {
                ignore_else(ts);
            }
        }
    } else if(function_key == "zero?") {
        auto number = construct_from_token(ts);
        f = new is_zero{number};
    } else if(function_key == "add1") {
        auto number = construct_from_token(ts);
        f = new self_add{number};
    } else if(function_key == "sub1") {
        auto number = construct_from_token(ts);
        f = new self_sub{number};
    } else if(context->is_in(function_key, true)) {
        auto params = std::shared_ptr<s_expression>(get_input_param(ts));
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

    auto pExpression = f->execute();
    std::cout << "-> " << f->name() << " -> " << f->return_type() << " [" << pExpression->get_value() << "]" << std::endl;
    return pExpression;
}

s_expression* get_input_param(Token_stream& ts) {
    auto params = new list();

    while(true) {
        const Token &token = ts.get();
        if(token.type != ')') {
            ts.put_back(token);
            auto p = std::unique_ptr<s_expression>(construct_from_token(ts));
            params->push_back(std::move(p));
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

    auto l = new list();
    while(true) {
        Token token = ts.get();
        if(token.type == 'A') {
            auto a = std::make_unique<atom>(token.value);
            l->push_back(std::move(a));
        } else if(token.type == 'B') {
            auto b = std::make_unique<boolean>(token.value == "#t" || token.value == "else");
            l->push_back(std::move(b));
        } else if(token.type == 'N') {
            auto i = std::make_unique<integer>(token.integer_value);
            l->push_back(std::move(i));
        } else if(token.type == ')') {
            break;
        } else if(token.type == '(') {
            ts.put_back(token);
            auto pList = std::unique_ptr<s_expression>(closure(ts));
            l->push_back(std::move(pList));
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

    auto params = collect_params(ts);
    if(params->get_indicator() != "list") {
        throw std::runtime_error("wrong syntax in function define!");
    }

    std::string body = get_func_body(ts, params);

    auto pDeclaration = new function_declaration{name.value, std::move(std::unique_ptr<s_expression>(params)), body};
    std::shared_ptr<function_declaration> func(pDeclaration);
    context->store(func);
    return pDeclaration;
}

s_expression* collect_params(Token_stream& ts) {
    const Token& left_bracket = ts.get();
    if(left_bracket.type != '(') {
        throw std::runtime_error("wrong syntax when declare parameters");
    }

    auto l = new list();
    while(true) {
        Token token = ts.get();
        if(token.type == 'A') {
            auto p = std::make_unique<param>(token.value);
            l->push_back(std::move(p));
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
    auto param_list = (list*)params;
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
