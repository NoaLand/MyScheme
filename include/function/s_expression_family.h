#ifndef MYSCHEME_S_EXPRESSION_FAMILY_H
#define MYSCHEME_S_EXPRESSION_FAMILY_H

#include "function.h"
#include "s_expression/atom.h"

class is_atom: public function {
public:
    explicit is_atom(s_expression* exp): s_exp(exp) {}
    boolean* execute() override;
    std::string return_type() override { return "bool"; }
    std::string name() override { return "atom?"; }
    std::string family() override { return "s_expression"; }
    ~is_atom() override { delete execute_res; }
private:
    s_expression* s_exp;
    boolean* execute_res{};
};

class is_eq: public function {
public:
    is_eq(s_expression* l, s_expression* r): left(l), right(r) {}
    boolean* execute() override;
    std::string return_type() override { return "bool"; }
    std::string name() override { return "eq?"; }
    std::string family() override { return "s_expression"; }
    ~is_eq() override { delete execute_res; }
private:
    s_expression* left;
    s_expression* right;
    boolean* execute_res{};
};

class is_number: public function {
public:
    explicit is_number(s_expression* exp): s_exp(exp) {}
    boolean* execute() override;
    std::string return_type() override { return "bool"; }
    std::string name() override { return "number?"; }
    std::string family() override { return "s_expression"; }
    ~is_number() override { delete execute_res; }
private:
    s_expression* s_exp;
    boolean* execute_res{};
};
#endif //MYSCHEME_S_EXPRESSION_FAMILY_H
