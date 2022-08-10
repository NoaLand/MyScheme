#ifndef MYSCHEME_S_EXPRESSION_FAMILY_H
#define MYSCHEME_S_EXPRESSION_FAMILY_H

#include "function.h"
#include "../s_expression/atom.h"

class is_atom: public function {
public:
    is_atom(s_expression* exp): s_exp(exp) {}
    atom* execute() override;
private:
    s_expression* s_exp;
};

class is_eq: public function {
public:
    is_eq(s_expression* l, s_expression* r): left(l), right(r) {}
    atom* execute() override;
private:
    s_expression* left;
    s_expression* right;
};

#endif //MYSCHEME_S_EXPRESSION_FAMILY_H
