#include "list.h"

std::string list::get_value() {
    std::string res = "( ";
    for (const auto& atom : l) {
        res += atom->get_value();
        res += " ";
    }
    res += ")";

    return res;
}

void list::push_back(std::unique_ptr<s_expression> s_exp) {
    if(s_exp->get_indicator() != "integer" && indicator == "tuple") {
        indicator = "list";
    }
    l.push_back(std::move(s_exp));
}

void list::print(std::ostream &os) {
    os << get_indicator() << ": " << get_value() << std::endl;
}

std::unique_ptr<s_expression>& list::get(int index) {
    return l.at(index);
}

bool list::has_value(std::string value) {
    for(const auto& element : l) {
        if(element->get_value() == value) {
            return true;
        }
    }

    return false;
}
