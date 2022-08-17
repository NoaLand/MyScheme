#ifndef MYSCHEME_LIST_FAMILY_H
#define MYSCHEME_LIST_FAMILY_H

#include "function.h"
#include "../s_expression/atom.h"

class car: public function {
public:
    explicit car(s_expression* exp): s_exp(exp) {
        if(s_exp->get_indicator() != "list" && s_exp->get_indicator() != "tuple") {
            throw std::runtime_error("wrong syntax, car can only get list.");
        }
    }
    s_expression* execute() override;
    std::string return_type() override { return "s_expression"; }
    std::string name() override { return "car"; }
private:
    s_expression* s_exp;
};

class cdr: public function {
public:
    explicit cdr(s_expression* exp): s_exp(exp) {
        if(s_exp->get_indicator() != "list" && s_exp->get_indicator() != "tuple") {
            throw std::runtime_error("wrong syntax, cdr can only get list.");
        }
    }
    s_expression* execute() override;
    std::string return_type() override { return "list"; }
    std::string name() override { return "cdr"; }
private:
    s_expression* s_exp;
};

class cons: public function {
public:
    cons(s_expression* l, s_expression* r): left(l), right(r) {
        if(r->get_indicator() != "list" && r->get_indicator() != "tuple") {
            throw std::runtime_error("wrong syntax, the second argument to cons must be a list.");
        }
    }
    s_expression* execute() override;
    std::string return_type() override { return "list"; }
    std::string name() override { return "cons"; }
private:
    s_expression* left;
    s_expression* right;
};

class is_null: public function {
public:
    explicit is_null(s_expression* exp): s_exp(exp) {
        if(exp->get_indicator() != "list" && exp->get_indicator() != "tuple") {
            throw std::runtime_error("wrong syntax, null? is defined only for lists.");
        }
    }
    boolean* execute() override;
    std::string return_type() override { return "bool"; }
    std::string name() override { return "null?"; }
private:
    s_expression* s_exp;
};

class add_tuple: public function {
public:
    explicit add_tuple(s_expression* tp): tup_list(tp) {
        if(tp->get_indicator() != "tuple") {
            throw std::runtime_error("wrong syntax, null? is defined only for lists.");
        }
    }
    integer* execute() override;
    std::string return_type() override { return "integer"; }
    std::string name() override { return "addtup"; }
private:
    s_expression* tup_list;
};
#endif //MYSCHEME_LIST_FAMILY_H
