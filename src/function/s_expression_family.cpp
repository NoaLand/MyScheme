#include "function/s_expression_family.h"

boolean* is_atom::execute() {
    const auto& type_info = s_exp->get_indicator();
    if(type_info == "atom" || type_info == "bool" || type_info == "integer") {
        execute_res = new boolean{true};
    } else {
        execute_res = new boolean{false};
    }

    return execute_res;
}

boolean* is_eq::execute() {
    if(left->get_indicator() == right->get_indicator()
        && left->get_value() == right->get_value()) {
        execute_res = new boolean{true};
    } else {
        execute_res = new boolean{false};
    }

    return execute_res;
}

boolean* is_number::execute() {
    const auto& type_info = s_exp->get_indicator();
    if(type_info == "integer") {
        execute_res = new boolean{true};
    } else {
        execute_res = new boolean{false};
    }

    return execute_res;
}
