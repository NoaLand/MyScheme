#ifndef MYSCHEME_LIST_FAMILY_H
#define MYSCHEME_LIST_FAMILY_H

#include <numeric>

#include "function.h"
#include "s_expression/atom.h"
#include "s_expression/list.h"

class car: public function {
public:
    explicit car(s_expression* exp) {
        if(exp->get_indicator() != "list" && exp->get_indicator() != "tuple") {
            throw std::runtime_error("wrong syntax, car can only get list.");
        }
        s_exp = reinterpret_cast<list<s_expression>*>(exp);
    }
    s_expression* execute() override;
    std::string return_type() override { return "s_expression"; }
    std::string name() override { return "car"; }
    std::string family() override { return "list"; }
private:
    list<s_expression>* s_exp;
};

class cdr: public function {
public:
    explicit cdr(s_expression* exp) {
        if(exp->get_indicator() != "list" && exp->get_indicator() != "tuple") {
            throw std::runtime_error("wrong syntax, cdr can only get list.");
        }
        s_exp = reinterpret_cast<list<s_expression>*>(exp);
    }
    list<s_expression>* execute() override;
    std::string return_type() override { return "list"; }
    std::string name() override { return "cdr"; }
    std::string family() override { return "list"; }
    ~cdr() override {
        delete execute_res;
    }
private:
    list<s_expression>* s_exp;
    list<s_expression>* execute_res{};
};

class cons: public function {
public:
    cons(s_expression* l, s_expression* r): left(l) {
        if(r->get_indicator() != "list" && r->get_indicator() != "tuple") {
            throw std::runtime_error("wrong syntax, the second argument to cons must be a list.");
        }
        right = reinterpret_cast<list<s_expression>*>(r);
    }
    list<s_expression>* execute() override;
    std::string return_type() override { return "list"; }
    std::string name() override { return "cons"; }
    std::string family() override { return "list"; }
    ~cons() override {
        delete execute_res;
    }
private:
    s_expression* left;
    list<s_expression>* right;
    list<s_expression>* execute_res{};
};

class is_null: public function {
public:
    explicit is_null(s_expression* exp) {
        if(exp->get_indicator() != "list" && exp->get_indicator() != "tuple") {
            throw std::runtime_error("wrong syntax, null? is defined only for lists.");
        }
        s_exp = reinterpret_cast<list<s_expression>*>(exp);
    }
    boolean* execute() override;
    std::string return_type() override { return "bool"; }
    std::string name() override { return "null?"; }
    std::string family() override { return "list"; }
    ~is_null() override {
        delete execute_res;
    }
private:
    list<s_expression>* s_exp;
    boolean* execute_res{};
};

class add_tuple: public function {
public:
    explicit add_tuple(s_expression* tp) {
        if(tp->get_indicator() != "tuple") {
            throw std::runtime_error("wrong syntax, null? is defined only for lists.");
        }
        tup_list = reinterpret_cast<list<integer>*>(tp);
    }
    integer* execute() override;
    std::string return_type() override { return "integer"; }
    std::string name() override { return "addtup"; }
    std::string family() override { return "list"; }
    ~add_tuple() override {
        delete execute_res;
    }
private:
    list<integer>* tup_list;
    integer* execute_res{};
};
#endif //MYSCHEME_LIST_FAMILY_H
