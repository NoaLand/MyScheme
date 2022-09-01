#include "s_expression/function_declaration.h"

std::string function_declaration::get_value() {
    std::string func;
    func += "-> name: " + name + "\n";
    func += "-> var: " + params->get_value() + "\n";
    func += "-> body: " + serialize_token_list(body);

    return func;
}

void function_declaration::print(std::ostream &os) {
    os << "---- func ----" << std::endl
        << get_value() << std::endl;
}