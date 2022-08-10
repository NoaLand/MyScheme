#ifndef MYSCHEME_FUNCTION_H
#define MYSCHEME_FUNCTION_H

#include "../s_expression/s_expression.h"

class function {
public:
    virtual s_expression* execute() = 0;
};
#endif //MYSCHEME_FUNCTION_H
