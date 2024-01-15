#include "core/interpreter.h"

auto interpreter::construct_from_token() -> std::shared_ptr<s_expression> {
    auto token = ts.get();
    std::shared_ptr<s_expression> s_exp;
    if(token.type == 'A') {
        s_exp = std::make_shared<atom>(token.value);
    } else if(token.type == 'B') {
        s_exp = std::make_shared<boolean>(token.value == "#t" || token.value == "else");
    } else if(token.type == 'N') {
        s_exp = std::make_shared<integer>(token.integer_value);
    } else if(token.type == 'P') {
        return std::shared_ptr<s_expression>(get_param_val(token));
    }  else {
        ts.put_back(token);
        s_exp = closure();
    }

    return s_exp;
}

auto interpreter::scheme() -> void {
    std::ostream& os = ts.get_ostream();
    os << "> ";
    auto token = ts.get();
    switch (token.type) {
        case 'A': {
            auto s_exp = atom{token.value};
            s_exp.print(os);
            break;
        }
        case 'B': {
            auto s_exp = boolean{token.value};
            s_exp.print(os);
            break;
        }
        case 'N': {
            auto s_exp = integer{token.integer_value};
            s_exp.print(os);
            break;
        }
        case '(': {
            ts.put_back(token);
            auto s_exp = closure();
            s_exp->print(os);
            break;
        }
        case ')':
            break;
        case 'F': {
            throw std::runtime_error("function **" + token.value + "** can only call in closure!");
        }
        case 'D': {
            throw std::runtime_error("function definition can only inside closure!");
        }
        default:
            os << "others: " << token.value << std::endl;
            break;
    }
}

auto interpreter::closure() -> std::shared_ptr<s_expression> {
    const Token& left = ts.get();

    if(left.type == 'P') {
        return std::shared_ptr<s_expression>(get_param_val(left));
    }

    if(left.type != '(') {
        throw std::runtime_error("wrong syntax: " + left.value);
    }

    auto l = std::make_shared<list<s_expression>>();
    while(true) {
        auto token = ts.get();
        if(token.type == 'A') {
            auto a = std::make_shared<atom>(token.value);
            l->push_back(a);
        } else if(token.type == 'B') {
            auto b = std::make_shared<boolean>(token.value == "#t" || token.value == "else");
            l->push_back(b);
        } else if(token.type == 'N') {
            auto i = std::make_shared<integer>(token.integer_value);
            l->push_back(i);
        } else if(token.type == ')') {
            break;
        } else if(token.type == '(') {
            ts.put_back(token);
            auto pList = reinterpret_pointer_cast<list<s_expression>>(closure());
            l->push_back(pList);
        } else if(token.type == 'F') {
            ts.put_back(token);
            return call_function();
        } else if(token.type == 'D') {
            ts.put_back(token);
            auto func = function_define();
            context.store(func);
            return func;
        } else if(token.type == 'P') {
            // TODO: refactor this, this token must be an anonymous function
            auto instance = call_stack.top();
            auto map_result = instance.param_hashmap.find(token.value)->second;
            if(map_result->get_indicator() == "anonymous_func") {
                auto func = dynamic_pointer_cast<anonymous_func>(map_result);
                ts.put_back(Token{'F', func->get_value()});
            } else if(map_result->get_indicator() == "customized_function") {
                auto func = dynamic_pointer_cast<function_declaration>(map_result);
                ts.put_back(Token{'F', func->get_name()});
            }
            return call_function();
        }
    }

    return l;
}

auto interpreter::call_function() -> std::shared_ptr<s_expression> {
    auto func = ts.get();
    auto& function_key = func.value;
    std::shared_ptr<function> f;
    if(function_key == "quote") {
        auto any = construct_from_token();
        f = std::make_shared<quote>(any);
    } else if(function_key == "car") {
        auto s_exp = closure();
        f = std::make_shared<car>(s_exp);
    } else if(function_key == "cdr") {
        auto s_exp = closure();
        f = std::make_shared<cdr>(s_exp);
    } else if(function_key == "cons") {
        auto left = construct_from_token();
        auto right = closure();
        f = std::make_shared<cons>(left, right);
    } else if(function_key == "null?") {
        auto s_exp = closure();
        f = std::make_shared<is_null>(s_exp);
    } else if(function_key == "addtup") {
        auto s_exp = construct_from_token();
        f = std::make_shared<add_tuple>(s_exp);
    } else if(function_key == "atom?") {
        auto s_exp = construct_from_token();
        f = std::make_shared<is_atom>(s_exp);
    } else if(function_key == "eq?") {
        auto left = construct_from_token();
        auto right = construct_from_token();
        f = std::make_shared<is_eq>(left, right);
    } else if(function_key == "number?") {
        auto s_exp = construct_from_token();
        f = std::make_shared<is_number>(s_exp);
    } else if(function_key == "or?") {
        auto left = construct_from_token();
        auto right = construct_from_token();
        f = std::make_shared<or_logic>(left, right);
    } else if(function_key == "and?") {
        auto left = construct_from_token();
        auto right = construct_from_token();
        f = std::make_shared<and_logic>(left, right);
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
            if(dynamic_pointer_cast<boolean>(assertion)->val()) {
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
        f = std::make_shared<is_zero>(number);
    } else if(function_key == "add1") {
        auto number = construct_from_token();
        f = std::make_shared<self_add>(number);
    } else if(function_key == "sub1") {
        auto number = construct_from_token();
        f = std::make_shared<self_sub>(number);
    } else if(context.is_in(function_key, true)) {
        auto params = get_input_param();
        function_instance instance{context.load(params), params};
        call_stack.push(instance);
        ts.push_back(instance.body);
        auto res = closure();
        call_stack.pop();
        return res;
    } else if(!call_stack.empty()) {
        // handle anonymous function
        auto func_instance = call_stack.top();
        if(!func_instance.local_function_hashmap.empty() && func_instance.local_function_hashmap.find(function_key) != func_instance.local_function_hashmap.end()) {
            // first call anonymous function
            auto params = get_input_param();
            auto func_declaration = func_instance.local_function_hashmap.find(function_key)->second;

            function_instance instance{func_declaration, params};
            call_stack.push(instance);
            ts.push_back(func_declaration->get_body());
            auto res = closure();
            call_stack.pop();
            return res;
        } else if(func_instance.func_name == function_key) {
            // after calling(function has been on the top of the stack)
            auto func_params = std::make_shared<list<param>>();
            for(int index = 0; index < func_instance.param_list->size_of(); index++){
                func_params->push_back(func_instance.param_list->get(index));
            }
            auto func_declaration = std::make_shared<function_declaration>(func_instance.func_name, func_params, func_instance.body);

            auto params = get_input_param();
            function_instance instance{func_declaration, params};
            call_stack.push(instance);
            ts.push_back(func_instance.body);
            auto res = closure();
            call_stack.pop();
            return res;
        }
    }

    const auto end = ts.get();
    if(end.type != ')') {
        throw std::runtime_error("wrong syntax: " + end.value);
    }

    auto pExpression = f->execute();
    ts.get_ostream() << "-> " << f->name() << " -> " << f->return_type() << " [" << pExpression->get_value() << "]" << std::endl;
    return std::shared_ptr<s_expression>(pExpression);
}

auto interpreter::get_input_param() -> std::shared_ptr<list<s_expression>> {
    auto params = std::make_shared<list<s_expression>>();

    while(true) {
        const auto& token = ts.get();
        if(token.type != ')') {
            std::shared_ptr<s_expression> p;
            if(token.type == 'F') {
                p = std::make_shared<anonymous_func>(token.value);
            } else {
                auto func = ts.get();
                if(func.type == 'D') {
                    ts.put_back(token);
                    p = function_define();
                    ts.get();
                } else {
                    ts.put_back(func);
                    ts.put_back(token);
                    p = construct_from_token();
                }
            }
            params->push_back(p);
        } else {
            break;
        }
    }

    return params;
}

auto interpreter::get_param_val(const Token &t) -> std::shared_ptr<s_expression> {
    auto instance = call_stack.top();
    auto map_result = instance.param_hashmap.find(t.value);

    return map_result->second;
}

auto interpreter::function_define() -> std::shared_ptr<function_declaration> {
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
    auto body = get_func_body(name.value, params);

    return std::make_shared<function_declaration>(name.value, params, body);
}

auto interpreter::collect_params() -> std::shared_ptr<list<param>> {
    const auto& left_bracket = ts.get();
    if(left_bracket.type != '(') {
        throw std::runtime_error("wrong syntax when declare parameters");
    }

    auto l = std::make_shared<list<param>>();
    while(true) {
        auto token = ts.get();
        if(token.type == 'A') {
            auto p = std::make_shared<param>(token.value);
            l->push_back(p);
        } else if(token.type == ')') {
            break;
        } else {
            throw std::runtime_error("wrong syntax when declare parameters");
        }
    }

    return l;
}

auto interpreter::get_func_body(const std::string& func_name, std::shared_ptr<list<param>> params) -> std::vector<Token> {
    auto body = std::vector<Token>();
    const auto& left_bracket = ts.get();
    if(left_bracket.type != '(') {
        throw std::runtime_error("wrong syntax when declare function deserialized_body");
    }
    auto brackets = 1;

    body.push_back(left_bracket);

    while(true) {
        auto token = ts.get();
        if(params->has_value(token.value)) {
            body.emplace_back('P', token.value);
        } else if (token.value == func_name){
            body.emplace_back('F', token.value);
        } else {
            body.push_back(token);
        }

        if(token.type == '(') {
            ++brackets;
        } else if(token.type == ')') {
            --brackets;
        }

        if(brackets == 0) {
            break;
        }
    }

    const auto& right_bracket = ts.get();
    if(right_bracket.type != ')') {
        throw std::runtime_error("wrong syntax when declare function deserialized_body");
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
