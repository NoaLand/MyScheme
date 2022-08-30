#include "core/function_context.h"

void function_context::store(function_declaration* func) {
    for(const auto& f: func_list) {
        if(f->get_name() == func->get_name()) {
            throw std::runtime_error("function has been declared!");
        }
    }

    func_list.push_back(func);
}

bool function_context::is_in(const std::string& name, bool load_to_buffer) {
    for(const auto& f: func_list) {
        if(f->get_name() == name) {
            if(load_to_buffer) {
                buffer.push(f);
            }
            return true;
        }
    }

    return false;
}

std::string function_context::instantiate(list<s_expression>* input_params) {
    auto func_define = buffer.top();
    buffer.pop();

    auto params = func_define->get_params();
    if(input_params->size_of() != params->size_of()) {
        throw std::runtime_error("wrong numbers of params!");
    }
    auto body = func_define->get_serialized_body();

    for(int index = 0; index < params->size_of(); ++index) {
        auto replace = " $" + params->get(index)->get_value() + "$ ";
        auto value = " " + input_params->get(index)->get_value() + " ";

        while (body.find(replace) != std::string::npos)
            body.replace(body.find(replace), replace.size(), value);
    }

    return body;
}
