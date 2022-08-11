#ifndef MYSCHEME_FUNCTION_DECLARATION_H
#define MYSCHEME_FUNCTION_DECLARATION_H
#include <string>
#include <utility>
#include <iostream>

#include "s_expression.h"

class function_declaration: public s_expression {
public:
    function_declaration(std::string n, s_expression* p, std::string b): name(std::move(n)), params(p), body(std::move(b)) {}
    std::string get_value() override;
    std::string get_indicator() override { return indicator; }
    void print(std::ostream& os) override;
private:
    std::string indicator{"customized_function"};
    std::string name;
    s_expression* params;
    std::string body;
};

#endif //MYSCHEME_FUNCTION_DECLARATION_H
