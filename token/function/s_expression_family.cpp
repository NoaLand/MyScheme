#include "s_expression_family.h"

boolean* is_atom::execute() {
    if(s_exp->get_indicator() == "atom") {
        return new boolean{true};
    } else {
        return new boolean{false};
    }
}

boolean *is_eq::execute() {
    if(left->get_indicator() == right->get_indicator()
        && left->get_value() == right->get_value()) {
        return new boolean{true};
    } else {
        return new boolean{false};
    }
}
