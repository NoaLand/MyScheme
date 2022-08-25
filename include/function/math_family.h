#ifndef MYSCHEME_MATH_FAMILY_H
#define MYSCHEME_MATH_FAMILY_H

#include "function.h"
#include "s_expression/atom.h"

class self_add: public function {
public:
    explicit self_add(s_expression* n) {
        if(n->get_indicator() != "integer") {
            throw std::runtime_error("wrong syntax: add1 need integer as param!");
        }
        number = dynamic_cast<integer*>(n);
    }
    integer* execute() override;
    std::string return_type() override { return "integer"; }
    std::string name() override { return "add1"; }
    std::string family() override { return "math"; }
private:
    integer* number;
};

class self_sub: public function {
public:
    explicit self_sub(s_expression* n) {
        if(n->get_indicator() != "integer") {
            throw std::runtime_error("wrong syntax: sub1 need integer as param!");
        }
        number = dynamic_cast<integer*>(n);
    }
    integer* execute() override;
    std::string return_type() override { return "integer"; }
    std::string name() override { return "sub1"; }
    std::string family() override { return "math"; }
private:
    integer* number;
};

class is_zero: public function {
public:
    explicit is_zero(s_expression* n) {
        if(n->get_indicator() != "integer") {
            throw std::runtime_error("wrong syntax: zero? need integer as param!");
        }
        number = dynamic_cast<integer*>(n);
    }
    boolean* execute() override;
    std::string return_type() override { return "bool"; }
    std::string name() override { return "zero?"; }
    std::string family() override { return "math"; }
private:
    integer* number;
};
#endif //MYSCHEME_MATH_FAMILY_H
