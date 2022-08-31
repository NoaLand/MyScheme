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
    
    auto res = new list<s_expression>();
    for(int index = 1; index < s_exp->size_of(); ++index) {
        res->push_back(s_exp->get(index));
    }

    return res;
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
    auto sum = 0;
    for(const auto& item : tup_list->get_iterator()) {
        sum += item->val();
    }

    return new integer{sum};
}
