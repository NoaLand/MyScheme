#include "list_family.h"
#include "../s_expression/list.h"
#include "../s_expression/atom.h"

s_expression* car::execute() {
    if(s_exp->get_indicator() != "list") {
        throw std::runtime_error("wrong syntax, car can only get list.");
    }
    list* l = (list*)s_exp;
    if(l->empty()) {
        throw std::runtime_error("you cannot ask for the *car* of the empty list");
    }

    return l->get(0);
}

s_expression* cdr::execute() {
    if(s_exp->get_indicator() != "list") {
        throw std::runtime_error("wrong syntax, cdr can only get list.");
    }
    list* l = (list*)s_exp;
    if(l->empty()) {
        throw std::runtime_error("you cannot ask for the *cdr* of the empty list");
    }
    
    list* res = new list();
    for(int index = 1; index < l->size_of(); ++index) {
        res->push_back(l->get(index));
    }

    return res;
}

s_expression* cons::execute() {
    list* r = (list*)right;
    list* res = new list();
    res->push_back(left);
    for(int index = 0; index < r->size_of(); ++index) {
        res->push_back(r->get(index));
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