#ifndef MYSCHEME_INTERPRETER_H
#define MYSCHEME_INTERPRETER_H

#include "token/token.h"
#include "s_expression/atom.h"

#include "function/function.h"
#include "function/list_family.h"
#include "function/math_family.h"
#include "function/nor_logic_family.h"
#include "function/s_expression_family.h"
#include "function/others.h"

class interpreter {
public:
    interpreter(function_context& c, Token_stream& t_stream): context{c}, ts{t_stream} {};
    auto scheme() -> void;
private:
    function_context& context;
    Token_stream& ts;

    auto function_define() -> function_declaration*;
    auto construct_from_token() -> s_expression*;
    auto func() -> s_expression*;
    auto closure() -> s_expression*;
    auto get_input_param() -> list<s_expression>*;
    auto collect_params() -> list<param>*;
    auto get_func_body(list<param>* params) -> std::string;
    auto ignore_else() -> void;
};
#endif //MYSCHEME_INTERPRETER_H
