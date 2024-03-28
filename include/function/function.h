#ifndef MYSCHEME_FUNCTION_H
#define MYSCHEME_FUNCTION_H

#include <memory>

#include "s_expression/s_expression.h"

class function {
public:
    virtual std::shared_ptr<s_expression> execute() = 0;
    virtual std::string return_type() noexcept = 0;
    virtual std::string name() noexcept = 0;
    virtual std::string family() noexcept = 0;
    virtual ~function() = default;
};
#endif //MYSCHEME_FUNCTION_H
