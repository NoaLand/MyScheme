#include "function/others.h"

std::shared_ptr<s_expression> quote::execute() {
    return std::make_shared<atom>(exp->get_value());
}
