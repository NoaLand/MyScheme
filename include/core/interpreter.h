#ifndef MYSCHEME_INTERPRETER_H
#define MYSCHEME_INTERPRETER_H

#include <unordered_map>
#include <utility>

#include "core/function/function_context.h"

#include "token/token_stream.h"

#include "function/function.h"
#include "function/list_family.h"
#include "function/math_family.h"
#include "function/nor_logic_family.h"
#include "function/s_expression_family.h"
#include "function/others.h"

class function_instance {
public:
    function_instance(function_declaration* func, list<s_expression>* input) {
        func_name = func->get_name();
        body = func->get_body();
        auto param_list = *func->get_params();
        for(int index = 0; index < param_list.size_of(); index++) {
            param_hashmap[param_list.get(index)->get_value()] = input->get(index);
        }
    }

    std::string func_name;
    std::unordered_map<std::string, s_expression*> param_hashmap;
    std::vector<Token> body;
};

class interpreter {
public:
    interpreter(function_context& c, Token_stream& t_stream): context{c}, ts{t_stream} {};
    
    auto construct_from_token() -> s_expression*;

    auto scheme() -> void;
    auto closure() -> s_expression*;

    auto call_function() -> s_expression*;
    auto get_input_param() -> list<s_expression>*;
    auto get_param_val(const Token& t) -> s_expression*;

    auto function_define() -> function_declaration*;
    auto collect_params() -> list<param>*;
    auto get_func_body(const std::string& func_name, list<param>* params) -> std::vector<Token>;
private:
    function_context& context;
    Token_stream& ts;
    std::stack<function_instance> call_stack;

    auto ignore_else() -> void;
};
#endif //MYSCHEME_INTERPRETER_H
