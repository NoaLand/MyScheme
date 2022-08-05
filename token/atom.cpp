#include "atom.h"

std::string atom::get_value() {
    return value;
}

std::ostream &operator<<(std::ostream &os, atom a) {
    return os << "atom: " << a.get_value();
}
