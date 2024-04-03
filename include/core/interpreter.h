#ifndef MYSCHEME_INTERPRETER_H
#define MYSCHEME_INTERPRETER_H

#include <unordered_map>
#include <utility>

#include "core/function/function_context.h"
#include "core/function/function_factory.h"

#include "stream/token_stream.h"

#include "function/function.h"
#include "function/list_family.h"
#include "function/math_family.h"
#include "function/nor_logic_family.h"
#include "function/s_expression_family.h"
#include "function/others.h"

#include "s_expression/anonymous_func.h"

class interpreter {
public:
    explicit interpreter(Token_stream& t_stream): ts{t_stream}, context{t_stream.get_context()} {};

    std::shared_ptr<s_expression> construct_from_token();

    void scheme();
    std::shared_ptr<s_expression> closure();

    std::shared_ptr<s_expression> call_function();
    std::shared_ptr<list<s_expression>> get_input_param();
    std::shared_ptr<s_expression> get_param_val(const Token& t);

    std::shared_ptr<function_declaration> function_define();
    std::shared_ptr<list<param>> collect_params();
    std::vector<Token> get_func_body(const std::string& func_name, std::shared_ptr<list<param>> params);
private:
    function_context& context;
    Token_stream& ts;
    std::stack<function_instance> call_stack;

    void ignore_else();
};
#endif //MYSCHEME_INTERPRETER_H
