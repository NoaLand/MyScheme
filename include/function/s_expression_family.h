#ifndef MYSCHEME_S_EXPRESSION_FAMILY_H
#define MYSCHEME_S_EXPRESSION_FAMILY_H

#include "function.h"
#include "s_expression/atom.h"

class is_atom: public function {
public:
    explicit is_atom(std::shared_ptr<s_expression> exp): s_exp(exp) {}
    std::shared_ptr<s_expression> execute() override;
    std::string return_type() override { return "bool"; }
    std::string name() override { return "atom?"; }
    std::string family() override { return "s_expression"; }
private:
    std::shared_ptr<s_expression> s_exp;
};

class is_eq: public function {
public:
    is_eq(std::shared_ptr<s_expression> l, std::shared_ptr<s_expression> r): left(l), right(r) {}
    std::shared_ptr<s_expression> execute() override;
    std::string return_type() override { return "bool"; }
    std::string name() override { return "eq?"; }
    std::string family() override { return "s_expression"; }
private:
    std::shared_ptr<s_expression> left;
    std::shared_ptr<s_expression> right;
};

class is_number: public function {
public:
    explicit is_number(std::shared_ptr<s_expression> exp): s_exp(exp) {}
    std::shared_ptr<s_expression> execute() override;
    std::string return_type() override { return "bool"; }
    std::string name() override { return "number?"; }
    std::string family() override { return "s_expression"; }
private:
    std::shared_ptr<s_expression> s_exp;
};
#endif //MYSCHEME_S_EXPRESSION_FAMILY_H
