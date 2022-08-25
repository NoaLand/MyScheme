#include "list_family.h"

s_expression* car::execute() {
    if(s_exp->empty()) {
        throw std::runtime_error("you cannot ask for the *car* of the empty list");
    }

    return s_exp->get(0);
}

list* cdr::execute() {
    if(s_exp->empty()) {
        throw std::runtime_error("you cannot ask for the *cdr* of the empty list");
    }
    
    auto res = new list();
    for(int index = 1; index < s_exp->size_of(); ++index) {
        res->push_back(s_exp->get(index));
    }

    return res;
}

list* cons::execute() {
    auto res = new list();
    res->push_back(left);
    for(int index = 0; index < right->size_of(); ++index) {
        res->push_back(right->get(index));
    }

    return res;
}

boolean* is_null::execute() {
    if(s_exp->empty()) {
        return new boolean{true};
    } else {
        return new boolean{false};
    }
}

integer* add_tuple::execute() {
    auto sum = 0;
    auto tuple = dynamic_cast<list*>(tup_list);
    for(const auto& item : tuple->get_iterator()) {
        auto v = dynamic_cast<integer*>(item);
        sum += v->val();
    }

    return new integer{sum};
}
