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

std::string list::car() {
    if(l.empty()) {
        throw std::runtime_error("you cannot ask for the *car* of the empty list");
    }
    return l.at(0)->get_value();
}

void list::push_back(s_expression* s_exp) {
    l.push_back(s_exp);
}

void list::print(std::ostream &os) {
    os << "list: " << get_value() << std::endl;
}
