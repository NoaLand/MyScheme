#include "list.h"

std::string list::get_value() {
    std::string res = "( ";
    for (auto atom : l) {
        res += atom->get_value();
        res += " ";
    }
    res += ")";

    return res;
}

void list::push_back(s_expression* s_exp) {
    l.push_back(s_exp);
}

std::ostream &operator<<(std::ostream &os, list l) {
    return os << "list: " << l.get_value();
}
