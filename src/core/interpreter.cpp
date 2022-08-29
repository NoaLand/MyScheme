#include "core/interpreter.h"

auto interpreter::scheme() -> void {
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
                s_exp = new boolean{token.value};
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
                auto s_exp = closure();
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

auto interpreter::func() -> s_expression* {
    auto func = ts.get();
    auto& function_key = func.value;
    function* f;
    if(function_key == "quote") {
        auto any = construct_from_token();
        f = new quote{any};
    } else if(function_key == "car") {
        auto s_exp = closure();
        f = new car{s_exp};
    } else if(function_key == "cdr") {
        auto s_exp = closure();
        f = new cdr{s_exp};
    } else if(function_key == "cons") {
        auto left = construct_from_token();
        auto right = closure();
        f = new cons{left, right};
    } else if(function_key == "null?") {
        auto s_exp = closure();
        f = new is_null{s_exp};
    } else if(function_key == "addtup") {
        auto s_exp = construct_from_token();
        f = new add_tuple{s_exp};
    } else if(function_key == "atom?") {
        auto s_exp = construct_from_token();
        f = new is_atom{s_exp};
    } else if(function_key == "eq?") {
        auto left = construct_from_token();
        auto right = construct_from_token();
        f = new is_eq{left, right};
    } else if(function_key == "number?") {
        auto s_exp = construct_from_token();
        f = new is_number{s_exp};
    } else if(function_key == "or?") {
        auto left = construct_from_token();
        auto right = construct_from_token();
        f = new or_logic{left, right};
    } else if(function_key == "and?") {
        auto left = construct_from_token();
        auto right = construct_from_token();
        f = new and_logic{left, right};
    } else if(function_key == "cond") {
        while(true) {
            auto condition_start = ts.get();
            if(condition_start.type == ')') {
                ts.get();
            }
            auto assertion = construct_from_token();
            if(assertion->get_indicator() != "bool") {
                throw std::runtime_error("wrong syntax! assertion need to return bool!");
            }
            if(dynamic_cast<boolean*>(assertion)->val()) {
                auto res = construct_from_token();
                ts.get();
                ignore_else();
                return res;
            } else {
                ignore_else();
            }
        }
    } else if(function_key == "zero?") {
        auto number = construct_from_token();
        f = new is_zero{number};
    } else if(function_key == "add1") {
        auto number = construct_from_token();
        f = new self_add{number};
    } else if(function_key == "sub1") {
        auto number = construct_from_token();
        f = new self_sub{number};
    } else if(context.is_in(function_key, true)) {
        auto params = get_input_param();
        auto body = context.instantiate(params);
        ts.put_back(body);
        return closure();
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

auto interpreter::get_input_param() -> list<s_expression>* {
    auto params = new list<s_expression>();

    while(true) {
        const auto& token = ts.get();
        if(token.type != ')') {
            ts.put_back(token);
            const auto p = construct_from_token();
            params->push_back(p);
        } else {
            break;
        }
    }

    return params;
}

auto interpreter::closure() -> s_expression* {
    const Token& left = ts.get();
    if(left.type != '(') {
        throw std::runtime_error("wrong syntax: " + left.value);
    }

    auto l = new list<s_expression>();
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
            auto pList = dynamic_cast<list<s_expression>*>(closure());
            l->push_back(pList);
        } else if(token.type == 'F') {
            ts.put_back(token);
            return func();
        } else if(token.type == 'D') {
            ts.put_back(token);
            return function_define();
        } else {
            throw std::runtime_error("wrong syntax: " + token.value);
        }
    }

    return l;
}

auto interpreter::construct_from_token() -> s_expression* {
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
        s_exp = closure();
    }

    return s_exp;
}

auto interpreter::function_define() -> function_declaration* {
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

    auto params = collect_params();
    auto body = get_func_body(params);

    auto func = new function_declaration{name.value, params, body};
    context.store(func);
    return func;
}

auto interpreter::collect_params() -> list<param>* {
    const auto& left_bracket = ts.get();
    if(left_bracket.type != '(') {
        throw std::runtime_error("wrong syntax when declare parameters");
    }

    auto l = new list<param>();
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

auto interpreter::get_func_body(list<param>* params) -> std::string {
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

auto interpreter::ignore_else() -> void {
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
