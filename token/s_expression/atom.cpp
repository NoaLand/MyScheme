#include "atom.h"

std::string atom::get_value() {
    return value;
}

void atom::print(std::ostream &os) {
    os << "atom: " << get_value() << std::endl;
}

std::string boolean::get_value() {
    return value;
}

void boolean::print(std::ostream &os) {
    os << "bool: " << get_value() << std::endl;
}

bool boolean::val() {
    return get_value() == "#t";
}
