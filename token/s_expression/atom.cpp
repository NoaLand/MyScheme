#include "atom.h"

std::string atom::get_value() {
    return value;
}

void atom::print(std::ostream &os) {
    os << "atom: " << get_value() << std::endl;
}