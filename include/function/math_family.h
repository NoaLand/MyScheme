#ifndef MYSCHEME_MATH_FAMILY_H
#define MYSCHEME_MATH_FAMILY_H

#include "function.h"
#include "s_expression/atom.h"

class self_add: public function {
public:
    explicit self_add(const std::shared_ptr<s_expression>& n) {
        if(n->get_indicator() != "integer") {
            throw std::runtime_error("wrong syntax: add1 need integer as param!");
        }
        number = dynamic_pointer_cast<integer>(n);
    }
    std::shared_ptr<s_expression> execute() override;
    std::string return_type() noexcept override { return "integer"; }
    std::string name() noexcept override { return "add1"; }
    std::string family() noexcept override { return "math"; }
private:
    std::shared_ptr<integer> number;
};

class self_sub: public function {
public:
    explicit self_sub(const std::shared_ptr<s_expression>& n) {
        if(n->get_indicator() != "integer") {
            throw std::runtime_error("wrong syntax: sub1 need integer as param!");
        }
        number = dynamic_pointer_cast<integer>(n);
    }
    std::shared_ptr<s_expression> execute() override;
    std::string return_type() noexcept override { return "integer"; }
    std::string name() noexcept override { return "sub1"; }
    std::string family() noexcept override { return "math"; }
private:
    std::shared_ptr<integer> number;
};

class is_zero: public function {
public:
    explicit is_zero(const std::shared_ptr<s_expression>& n) {
        if(n->get_indicator() != "integer") {
            throw std::runtime_error("wrong syntax: zero? need integer as param!");
        }
        number = dynamic_pointer_cast<integer>(n);
    }
    std::shared_ptr<s_expression> execute() override;
    std::string return_type() noexcept override { return "bool"; }
    std::string name() noexcept override { return "zero?"; }
    std::string family() noexcept override { return "math"; }
private:
    std::shared_ptr<integer> number;
};
#endif //MYSCHEME_MATH_FAMILY_H
