#ifndef MYSCHEME_MATH_FAMILY_H
#define MYSCHEME_MATH_FAMILY_H

#include "function.h"
#include "../s_expression/atom.h"

class self_add: public function {
public:
    self_add(s_expression* n): number(n) {
        if(number->get_indicator() != "integer") {
            throw std::runtime_error("wrong syntax: add1 need integer as param!");
        }
    }
    integer* execute() override;
    std::string return_type() override { return "integer"; }
    std::string name() override { return "add1"; }
private:
    s_expression* number;
};

class self_sub: public function {
public:
    self_sub(s_expression* n): number(n) {
        if(number->get_indicator() != "integer") {
            throw std::runtime_error("wrong syntax: sub1 need integer as param!");
        }
    }
    integer* execute() override;
    std::string return_type() override { return "integer"; }
    std::string name() override { return "sub1"; }
private:
    s_expression* number;
};

class is_zero: public function {
public:
    is_zero(s_expression* n): number(n) {
        if(number->get_indicator() != "integer") {
            throw std::runtime_error("wrong syntax: zero? need integer as param!");
        }
    }
    boolean* execute() override;
    std::string return_type() override { return "bool"; }
    std::string name() override { return "zero?"; }
private:
    s_expression* number;
};
#endif //MYSCHEME_MATH_FAMILY_H
