#include "function/math_family.h"

integer* self_add::execute() {
    return new integer(number->val() + 1);
}

integer* self_sub::execute() {
    return new integer(number->val() - 1);
}

boolean *is_zero::execute() {
    return new boolean{number->val() == 0};
}
