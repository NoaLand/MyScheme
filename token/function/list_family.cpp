#include "list_family.h"
#include "../s_expression/list.h"

s_expression* car::execute() {
    list* l = (list*)s_exp;
    if(l->empty()) {
        throw std::runtime_error("you cannot ask for the *car* of the empty list");
    }

    std::unique_ptr<s_expression>& res = l->get(0);
    return res.get();
}

s_expression* cdr::execute() {
    list* l = (list*)s_exp;
    if(l->empty()) {
        throw std::runtime_error("you cannot ask for the *cdr* of the empty list");
    }
    
    list* res = new list();
    for(int index = 1; index < l->size_of(); ++index) {
        res->push_back(std::move(l->get(index)));
    }

    return res;
}

s_expression* cons::execute() {
    list* r = (list*)right;
    list* res = new list();
    res->push_back(std::unique_ptr<s_expression>(left));
    for(int index = 0; index < r->size_of(); ++index) {
        res->push_back(std::move(r->get(index)));
    }

    return res;
}

boolean* is_null::execute() {
    list *pList = (list *) s_exp;
    if(pList->empty()) {
        return new boolean{true};
    } else {
        return new boolean{false};
    }
}

integer* add_tuple::execute() {
    int sum = 0;
    list* tuple = (list*) tup_list;
    for(const auto& item : tuple->get_iterator()) {
        auto v = (integer*)item.get();
        sum += v->val();
    }

    return new integer{sum};
}
