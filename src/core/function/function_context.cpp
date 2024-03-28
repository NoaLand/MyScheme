#include "core/function/function_context.h"

void function_context::store(const std::shared_ptr<function_declaration>& func) {
    for(const auto& f: func_list) {
        if(f->get_name() == func->get_name()) {
            throw std::runtime_error("function has been declared!");
        }
    }

    func_list.push_back(func);
}

bool function_context::is_in(const std::string& name, const bool& load_to_buffer) {
    return std::any_of(func_list.begin(), func_list.end(), [&name, &load_to_buffer, this] (const auto& f) mutable {
        if(f->get_name() == name) {
            if (load_to_buffer) {
                buffer.push(f);
            }
            return true;
        }
        return false;
    });
}

std::shared_ptr<function_declaration> function_context::load(const std::shared_ptr<list<s_expression>>& input_params) {
    auto func_define = buffer.top();
    buffer.pop();

    auto params = func_define->get_params();
    if(input_params->size_of() != params->size_of()) {
        throw std::runtime_error("wrong numbers of params!");
    }

    return func_define;
}
