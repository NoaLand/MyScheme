#ifndef MYSCHEME_FUNCTION_H
#define MYSCHEME_FUNCTION_H

#include "../s_expression/s_expression.h"

class function {
public:
    virtual s_expression* execute() = 0;
    virtual std::string return_type() = 0;
    virtual std::string name() = 0;
    virtual std::string family() = 0;
};
#endif //MYSCHEME_FUNCTION_H
