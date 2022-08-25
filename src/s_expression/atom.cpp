#include "s_expression/atom.h"

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

std::string integer::get_value() {
    return std::to_string(value);
}

void integer::print(std::ostream &os) {
    os << "integer: " << get_value() << std::endl;
}

int integer::val() const {
    return value;
}
