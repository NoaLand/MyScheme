#include "s_expression/atom.h"

std::string atom::get_value() noexcept {
    return value;
}

void atom::print(std::ostream &os) noexcept {
    os << "atom: " << get_value() << std::endl;
}

std::string boolean::get_value() noexcept {
    if(value == "else") {
        return "#t";
    }

    return value;
}

void boolean::print(std::ostream &os) noexcept {
    os << "bool: " << get_value() << std::endl;
}

bool boolean::val() {
    return get_value() == "#t" || get_value() == "else";
}

std::string integer::get_value() noexcept {
    return std::to_string(value);
}

void integer::print(std::ostream &os) noexcept {
    os << "integer: " << get_value() << std::endl;
}

int integer::val() const {
    return value;
}
