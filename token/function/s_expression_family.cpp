#include "s_expression_family.h"

boolean* is_atom::execute() {
    const auto& type_info = s_exp->get_indicator();
    if(type_info == "atom" || type_info == "bool" || type_info == "integer") {
        return new boolean{true};
    } else {
        return new boolean{false};
    }
}

boolean* is_eq::execute() {
    if(left->get_indicator() == right->get_indicator()
        && left->get_value() == right->get_value()) {
        return new boolean{true};
    } else {
        return new boolean{false};
    }
}

boolean* is_number::execute() {
    const auto& type_info = s_exp->get_indicator();
    if(type_info == "integer") {
        return new boolean{true};
    } else {
        return new boolean{false};
    }
}
