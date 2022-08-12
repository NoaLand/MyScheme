#include "function_declaration.h"
#include "list.h"

std::string function_declaration::get_value() {
    std::string func;
    func += "-> name: " + name + "\n";
    func += "-> var: " + params->get_value() + "\n";
    func += "-> body: " + body + "\n";

    return func;
}

void function_declaration::print(std::ostream &os) {
    os << "---- func ----" << std::endl
        << get_value() << std::endl;
}

void function_context::store(function_declaration* func) {
    for(const auto& f: func_list) {
        if(f->get_name() == func->get_name()) {
            throw std::runtime_error("function has been declared!");
        }
    }

    func_list.push_back(func);
}

bool function_context::is_in(const std::string& name) {
    for(const auto& f: func_list) {
        if(f->get_name() == name) {
            buffer = f;
            return true;
        }
    }

    return false;
}

std::string function_context::instantiate(s_expression* p) {
    if(p->get_indicator() != "list") {
        throw std::runtime_error("wrong params type!");
    }

    list* params = (list*)buffer->get_params();
    list* input_params = (list *) p;
    if(input_params->size_of() != params->size_of()) {
        throw std::runtime_error("wrong numbers of params!");
    }

    std::string body = buffer->get_body();
    for(int index = 0; index < params->size_of(); ++index) {
        std::string replace = " $" + params->get(index)->get_value() + "$ ";
        std::string value = " " + input_params->get(index)->get_value() + " ";

        while (body.find(replace) != std::string::npos)
            body.replace(body.find(replace), replace.size(), value);
    }

    return body;
}
