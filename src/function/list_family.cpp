#include "function/list_family.h"

s_expression* car::execute() {
    if(s_exp->empty()) {
        throw std::runtime_error("you cannot ask for the *car* of the empty list");
    }

    return s_exp->get(0);
}

list<s_expression>* cdr::execute() {
    if(s_exp->empty()) {
        throw std::runtime_error("you cannot ask for the *cdr* of the empty list");
    }

    auto iter = s_exp->get_iterator();
    return new list<s_expression>(iter.begin() + 1, iter.end());
}

list<s_expression>* cons::execute() {
    auto res = new list<s_expression>();
    res->push_back(left);
    for(int index = 0; index < right->size_of(); ++index) {
        res->push_back(right->get(index));
    }

    return res;
}

boolean* is_null::execute() {
    return new boolean{s_exp->empty()};
}

integer* add_tuple::execute() {
    auto tup = tup_list->get_iterator();

    return std::accumulate(tup.begin(), tup.end(), new integer{0},
                           [](const integer *l, const integer *r) { return new integer{l->val() + r->val()}; });
}
