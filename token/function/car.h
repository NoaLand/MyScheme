#ifndef MYSCHEME_CAR_H
#define MYSCHEME_CAR_H

#include "function.h"

class car: public function {
public:
    car(s_expression* exp): s_exp(exp) {}
    s_expression* execute() override;
private:
    s_expression* s_exp;
};


#endif //MYSCHEME_CAR_H
