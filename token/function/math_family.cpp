#include "math_family.h"

integer* self_add::execute() {
    int original_val = ((integer*)number)->val();

    return new integer(original_val + 1);
}

integer* self_sub::execute() {
    int original_val = ((integer*)number)->val();

    return new integer(original_val - 1);
}

boolean *is_zero::execute() {
    int original_val = ((integer*)number)->val();
    return new boolean{original_val == 0};
}
