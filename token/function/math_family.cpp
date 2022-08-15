#include "math_family.h"

integer* self_add::execute() {
    if(number->get_indicator() != "integer") {
        throw std::runtime_error("wrong syntax: add1 need integer as param!");
    }
    int original_val = ((integer*)number)->val();

    return new integer(original_val + 1);
}
