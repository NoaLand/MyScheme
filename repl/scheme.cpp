#include "../src/token/token.h"
#include "../src/token/s_expression/atom.h"
#include "../src/token/s_expression/list.h"
#include "../src/function/list_family.h"
#include "../src/function/s_expression_family.h"
#include "../src/token/s_expression/params.h"
#include "../src/token/s_expression/function_declaration.h"
#include "../src/function/nor_logic_family.h"
#include "../src/function/math_family.h"
#include "../src/function/others.h"

std::istream& is{std::cin};
function_context context;
Token_stream ts{is, &context};

void scheme(Token_stream& ts);
auto function_define(Token_stream& ts) -> function_declaration*;
auto construct_from_token(Token_stream& ts) -> s_expression*;
auto func(Token_stream& ts) -> s_expression*;
auto closure(Token_stream& ts) -> s_expression*;
auto get_input_param(Token_stream& ts) -> list*;

auto preload_libs() -> void;
auto ignore_else(Token_stream& ts) -> void;

auto preload_libs() -> void {
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

    context.store(lat);
    context.store(lat_length);
    context.store(is_member);
    context.store(rember);
    context.store(pick);
    context.store(rempick);
    context.store(add);
    context.store(sub);
    context.store(multiplication);
    context.store(divide);
    context.store(greater_than);
    context.store(less_than);
    context.store(equal);
    context.store(expt);
}

int main() {
    preload_libs();
    std::cout << "Let's start!" << std::endl;
    scheme(ts);
}

void scheme(Token_stream& ts) {
    while(ts.get_istream()) {
        std::cout << "> ";
        auto token = ts.get();
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
                auto s_exp = closure(ts);
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

auto func(Token_stream& ts) -> s_expression* {
    auto func = ts.get();
    auto& function_key = func.value;
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
            auto condition_start = ts.get();
            if(condition_start.type == ')') {
                ts.get();
            }
            auto assertion = construct_from_token(ts);
            if(assertion->get_indicator() != "bool") {
                throw std::runtime_error("wrong syntax! assertion need to return bool!");
            }
            if(dynamic_cast<boolean*>(assertion)->val()) {
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
    } else if(context.is_in(function_key, true)) {
        auto params = get_input_param(ts);
        auto body = context.instantiate(params);
        ts.put_back(body);
        return closure(ts);
    } else {
        throw std::runtime_error("unknown function: " + function_key);
    }

    const auto end = ts.get();
    if(end.type != ')') {
        throw std::runtime_error("wrong syntax: " + end.value);
    }

    auto pExpression = f->execute();
    std::cout << "-> " << f->name() << " -> " << f->return_type() << " [" << pExpression->get_value() << "]" << std::endl;
    return pExpression;
}

auto get_input_param(Token_stream& ts) -> list* {
    auto params = new list();

    while(true) {
        const auto& token = ts.get();
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

auto closure(Token_stream& ts) -> s_expression* {
    const Token& left = ts.get();
    if(left.type != '(') {
        throw std::runtime_error("wrong syntax: " + left.value);
    }

    auto l = new list();
    while(true) {
        auto token = ts.get();
        if(token.type == 'A') {
            auto a = new atom(token.value);
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
            auto pList = dynamic_cast<list*>(closure(ts));
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

auto construct_from_token(Token_stream& ts) -> s_expression* {
    auto token = ts.get();
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

auto collect_params(Token_stream& ts) -> list*;
auto get_func_body(Token_stream& ts, list* params) -> std::string;

auto function_define(Token_stream& ts) -> function_declaration* {
    auto define_keyword = ts.get();
    auto name = ts.get();
    if(name.type != 'A') {
        throw std::runtime_error("illegal func name!");
    }

    auto left_brackets = ts.get();

    auto lambda = ts.get();
    if(lambda.type != 'L') {
        throw std::runtime_error("wrong syntax in function define!");
    }

    auto params = collect_params(ts);
    auto body = get_func_body(ts, params);

    auto func = new function_declaration{name.value, params, body};
    context.store(func);
    return func;
}

auto collect_params(Token_stream& ts) -> list* {
    const auto& left_bracket = ts.get();
    if(left_bracket.type != '(') {
        throw std::runtime_error("wrong syntax when declare parameters");
    }

    auto l = new list();
    while(true) {
        auto token = ts.get();
        if(token.type == 'A') {
            auto p = new param(token.value);
            l->push_back(p);
        } else if(token.type == ')') {
            break;
        } else {
            throw std::runtime_error("wrong syntax when declare parameters");
        }
    }

    return l;
}

auto get_func_body(Token_stream& ts, list* params) -> std::string {
    const auto& left_bracket = ts.get();
    auto param_list = params;
    if(left_bracket.type != '(') {
        throw std::runtime_error("wrong syntax when declare function body");
    }
    auto brackets = 1;

    std::string body;
    body += left_bracket.type;

    while(true) {
        auto token = ts.get();
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

    const auto& right_bracket = ts.get();
    if(right_bracket.type != ')') {
        throw std::runtime_error("wrong syntax when declare function body");
    }

    return body;
}

auto ignore_else(Token_stream& ts) -> void {
    auto brackets = 1;
    while(true) {
        const auto& token = ts.get();
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
