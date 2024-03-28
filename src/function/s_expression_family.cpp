#include "function/s_expression_family.h"

std::shared_ptr<s_expression> is_atom::execute() {
    const auto& type_info = s_exp->get_indicator();
    if(type_info == "atom" || type_info == "bool" || type_info == "integer") {
        return std::make_unique<boolean>(true);
    } else {
        return std::make_unique<boolean>(false);
    }
}

std::shared_ptr<s_expression> is_eq::execute() {
    if(left->get_indicator() == right->get_indicator()
        && left->get_value() == right->get_value()) {
        return std::make_unique<boolean>(true);
    } else {
        return std::make_unique<boolean>(false);
    }
}

std::shared_ptr<s_expression> is_number::execute() {
    const auto& type_info = s_exp->get_indicator();
    if(type_info == "integer") {
        return std::make_unique<boolean>(true);
    } else {
        return std::make_unique<boolean>(false);
    }
}
