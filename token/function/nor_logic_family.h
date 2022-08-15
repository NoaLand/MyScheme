#ifndef MYSCHEME_NOR_LOGIC_FAMILY_H
#define MYSCHEME_NOR_LOGIC_FAMILY_H

#include "function.h"
#include "../s_expression/atom.h"

class or_logic: public function {
public:
    or_logic(s_expression* l, s_expression* r): left(l), right(r) {}
    boolean* execute() override;
    std::string return_type() override { return "bool"; }
    std::string name() override { return "or?"; }
private:
    s_expression* left;
    s_expression* right;
};


#endif //MYSCHEME_NOR_LOGIC_FAMILY_H
