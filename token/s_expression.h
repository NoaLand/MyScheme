#ifndef MYSCHEME_S_EXPRESSION_H
#define MYSCHEME_S_EXPRESSION_H
#include <string>
#include <iostream>
class s_expression {
public:
    virtual std::string get_value() = 0;
private:
    std::string indicator;
    std::string value;
};
#endif //MYSCHEME_S_EXPRESSION_H
