#include "function/list_family.h"

std::shared_ptr<s_expression> car::execute() {
    if(s_exp->empty()) {
        throw std::runtime_error("you cannot ask for the *car* of the empty list");
    }

    return s_exp->get(0);
}

std::shared_ptr<s_expression> cdr::execute() {
    if(s_exp->empty()) {
        throw std::runtime_error("you cannot ask for the *cdr* of the empty list");
    }

    auto iter = s_exp->get_iterator();

    return std::make_unique<list<s_expression>>(iter.begin() + 1, iter.end());
}

std::shared_ptr<s_expression> cons::execute() {
    std::unique_ptr<list<s_expression>> res = std::make_unique<list<s_expression>>();
    res->push_back(left);
    for(int index = 0; index < right->size_of(); ++index) {
        res->push_back(right->get(index));
    }

    return res;
}

std::shared_ptr<s_expression> is_null::execute() {
    return std::make_unique<boolean>(s_exp->empty());
}

std::shared_ptr<s_expression> add_tuple::execute() {
    auto tup = tup_list->get_iterator();

    int sum{0};
    for (const auto& e : tup) {
        sum += dynamic_pointer_cast<integer>(e)->val();
    }

    return std::make_unique<integer>(sum);
}
