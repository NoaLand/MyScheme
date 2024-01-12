#include "function/math_family.h"

integer* self_add::execute() {
    execute_res = new integer(number->val() + 1);

    return execute_res;
}

integer* self_sub::execute() {
    execute_res = new integer(number->val() - 1);

    return execute_res;
}

boolean *is_zero::execute() {
    execute_res =  new boolean{number->val() == 0};

    return execute_res;
}
