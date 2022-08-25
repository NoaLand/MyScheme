#include "math_family.h"

integer* self_add::execute() {
    return new integer(number->val() + 1);
}

integer* self_sub::execute() {
    return new integer(number->val() - 1);
}

boolean *is_zero::execute() {
    auto original_val = dynamic_cast<integer*>(number)->val();
    return new boolean{original_val == 0};
}
