#include "car.h"
#include "../s_expression/list.h"

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
