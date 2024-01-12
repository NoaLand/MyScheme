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
    execute_res = new list<s_expression>(iter.begin() + 1, iter.end());

    return execute_res;
}

list<s_expression>* cons::execute() {
    execute_res = new list<s_expression>();
    execute_res->push_back(left);
    for(int index = 0; index < right->size_of(); ++index) {
        execute_res->push_back(right->get(index));
    }

    return execute_res;
}

boolean* is_null::execute() {
    execute_res = new boolean{s_exp->empty()};

    return execute_res;
}

integer* add_tuple::execute() {
    auto tup = tup_list->get_iterator();

    int sum{0};
    for (const auto& e : tup) {
        sum += reinterpret_cast<integer*>(e)->val();
    }

    execute_res = new integer{sum};

    return execute_res;
}
