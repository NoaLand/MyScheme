#include "function/nor_logic_family.h"

std::shared_ptr<s_expression> or_logic::execute() {
    if(left->val()) {
        return std::make_shared<boolean>(true);
    } else {
        return std::make_shared<boolean>(right->val());
    }
}

std::shared_ptr<s_expression> and_logic::execute() {
    return std::make_shared<boolean>(left->val() && right->val());
}
