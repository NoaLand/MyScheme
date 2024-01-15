#ifndef MYSCHEME_S_EXPRESSION_H
#define MYSCHEME_S_EXPRESSION_H
#include <string>
#include <iostream>
class s_expression {
public:
    s_expression() = default;
    virtual std::string get_value() = 0;
    virtual std::string get_indicator() = 0;
    virtual void print(std::ostream&) = 0;
    virtual ~s_expression() = default;
};
#endif //MYSCHEME_S_EXPRESSION_H
