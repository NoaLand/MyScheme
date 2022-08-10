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

void list::print(std::ostream &os) {
    os << "list: " << get_value() << std::endl;
}

s_expression *list::get(int index) {
    return l.at(index);
}
