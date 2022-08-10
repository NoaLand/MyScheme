#include "s_expression_family.h"

atom* is_atom::execute() {
    if(s_exp->get_indicator() == "atom") {
        return new atom{"#t"};
    } else {
        return new atom{"#f"};
    }
}

atom *is_eq::execute() {
    if(left->get_indicator() == right->get_indicator()
        && left->get_value() == right->get_value()) {
        return new atom{"#t"};
    } else {
        return new atom{"#f"};
    }
}
