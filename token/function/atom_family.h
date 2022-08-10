#ifndef MYSCHEME_ATOM_FAMILY_H
#define MYSCHEME_ATOM_FAMILY_H

#include "function.h"

class is_atom: public function {
public:
    is_atom(s_expression* exp): s_exp(exp) {}
    s_expression* execute() override;
private:
    s_expression* s_exp;
};

#endif //MYSCHEME_ATOM_FAMILY_H
