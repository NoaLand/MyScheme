#ifndef MYSCHEME_S_EXPRESSION_H
#define MYSCHEME_S_EXPRESSION_H
#include <string>
#include <iostream>
class s_expression {
public:
    s_expression() = default;
    virtual std::string get_value() = 0;
};
#endif //MYSCHEME_S_EXPRESSION_H
