#ifndef MYSCHEME_LIST_FAMILY_H
#define MYSCHEME_LIST_FAMILY_H

#include "function.h"

class car: public function {
public:
    car(s_expression* exp): s_exp(exp) {}
    s_expression* execute() override;
private:
    s_expression* s_exp;
};

class cdr: public function {
public:
    cdr(s_expression* exp): s_exp(exp) {}
    s_expression* execute() override;
private:
    s_expression* s_exp;
};

class cons: public function {
public:
    cons(s_expression* l, s_expression* r): left(l), right(r) {
        if(r->get_indicator() != "list") {
            throw std::runtime_error("wrong syntax, the second argument to cons must be a list.");
        }
    }
    s_expression* execute() override;
private:
    s_expression* left;
    s_expression* right;
};

#endif //MYSCHEME_LIST_FAMILY_H
