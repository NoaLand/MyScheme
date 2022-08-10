#ifndef MYSCHEME_ATOM_H
#define MYSCHEME_ATOM_H
#include <string>
#include <utility>
#include <iostream>

#include "s_expression.h"

class atom: public s_expression {
public:
    atom(std::string v): value(std::move(v)) {}
    std::string get_value() override;
    std::string get_indicator() override { return indicator; }
    void print(std::ostream& os) override;
private:
    std::string indicator{"atom"};
    std::string value;
};
#endif //MYSCHEME_ATOM_H
