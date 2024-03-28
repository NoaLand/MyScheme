#include "s_expression/params.h"

std::string param::get_value() noexcept {
    return value;
}

void param::print(std::ostream &os) noexcept {
    os << "param: " << get_value() << std::endl;
}
