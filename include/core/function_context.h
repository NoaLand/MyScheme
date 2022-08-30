#ifndef MYSCHEME_FUNCTION_CONTEXT_H
#define MYSCHEME_FUNCTION_CONTEXT_H

#include <vector>
#include <stack>
#include "s_expression/function_declaration.h"


class function_context {
public:
    void store(function_declaration* func);
    bool is_in(const std::string& name, bool load_to_buffer = false);
    std::string instantiate(list<s_expression>* p);
private:
    std::vector<function_declaration*> func_list{};
    std::stack<function_declaration*> buffer;
};

#endif //MYSCHEME_FUNCTION_CONTEXT_H
