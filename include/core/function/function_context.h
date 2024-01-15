#ifndef MYSCHEME_FUNCTION_CONTEXT_H
#define MYSCHEME_FUNCTION_CONTEXT_H

#include <vector>
#include <stack>
#include "s_expression/function_declaration.h"


class function_context {
public:
    void store(std::shared_ptr<function_declaration> func);
    bool is_in(const std::string& name, bool load_to_buffer = false);
    std::shared_ptr<function_declaration> load(const std::shared_ptr<list<s_expression>>& p);
private:
    std::vector<std::shared_ptr<function_declaration>> func_list{};
    std::stack<std::shared_ptr<function_declaration>> buffer;
};

#endif //MYSCHEME_FUNCTION_CONTEXT_H
