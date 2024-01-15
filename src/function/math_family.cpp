#include "function/math_family.h"

std::shared_ptr<s_expression> self_add::execute() {
    return std::make_shared<integer>(number->val() + 1);
}

std::shared_ptr<s_expression> self_sub::execute() {
    return std::make_shared<integer>(number->val() - 1);
}

std::shared_ptr<s_expression> is_zero::execute() {
    return std::make_shared<boolean>(number->val() == 0);
}
