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


#endif //MYSCHEME_LIST_FAMILY_H
