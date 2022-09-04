#ifndef MYSCHEME_ANONYMOUS_FUNC_H
#define MYSCHEME_ANONYMOUS_FUNC_H

#include "s_expression/s_expression.h"

class anonymous_func: public s_expression {
public:
    anonymous_func() = default;
    explicit anonymous_func(std::string a): alias(std::move(a)) {}
    std::string get_value() override { return alias; }
    std::string get_indicator() override { return indicator; }
    void print(std::ostream& os) override { os << "anonymous func: " << get_value() << std::endl; }
private:
    std::string indicator{"anonymous_func"};
    std::string alias;
};
#endif //MYSCHEME_ANONYMOUS_FUNC_H
