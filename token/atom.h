#ifndef MYSCHEME_ATOM_H
#define MYSCHEME_ATOM_H
#include <string>
#include <utility>
#include <iostream>

#include "s_expression.h"

class atom: virtual public s_expression {
public:
    atom(std::string v): indicator("atom"), value(std::move(v)) {}
    std::string get_value();
private:
    std::string indicator;
    std::string value;
};

std::ostream& operator<<(std::ostream& os, atom a);
#endif //MYSCHEME_ATOM_H
