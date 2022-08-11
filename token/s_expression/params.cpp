#include "params.h"

std::string param::get_value() {
    return value;
}

void param::print(std::ostream &os) {
    os << "param: " << get_value() << std::endl;
}
