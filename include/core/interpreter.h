#ifndef MYSCHEME_INTERPRETER_H
#define MYSCHEME_INTERPRETER_H

#include "token/token.h"

#include "function/function.h"
#include "function/list_family.h"
#include "function/math_family.h"
#include "function/nor_logic_family.h"
#include "function/s_expression_family.h"
#include "function/others.h"

class interpreter {
public:
    interpreter(function_context& c, Token_stream& t_stream): context{c}, ts{t_stream} {};
    
    auto construct_from_token() -> s_expression*;

    auto scheme() -> void;
    auto closure() -> s_expression*;

    auto call_function() -> s_expression*;
    auto get_input_param() -> list<s_expression>*;

    auto function_define() -> function_declaration*;
    auto collect_params() -> list<param>*;
    auto get_func_body(const std::string& func_name, list<param>* params) -> std::string;
private:
    function_context& context;
    Token_stream& ts;

    auto ignore_else() -> void;
};
#endif //MYSCHEME_INTERPRETER_H
