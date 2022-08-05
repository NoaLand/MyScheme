#include "list.h"

std::string list::get_value() {
    std::string res = "( ";
    for (const auto& atom : list) {
        res += atom.value;
        res += " ";
    }
    res += ")";

    return res;
}

void list::push_back(Token token) {
    list.push_back(token);
}

std::ostream &operator<<(std::ostream &os, list sl) {
    return os << sl.get_value();
}
