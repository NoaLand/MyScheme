#ifndef MYSCHEME_LIST_FAMILY_H
#define MYSCHEME_LIST_FAMILY_H

#include <numeric>
#include <utility>

#include "function.h"
#include "s_expression/atom.h"
#include "s_expression/list.h"

class car: public function {
public:
    explicit car(std::shared_ptr<s_expression> exp) {
        if(exp->get_indicator() != "list" && exp->get_indicator() != "tuple") {
            throw std::runtime_error("wrong syntax, car can only get list.");
        }
        s_exp = static_pointer_cast<list<s_expression>>(exp);
    }
    std::shared_ptr<s_expression> execute() override;
    std::string return_type() override { return "s_expression"; }
    std::string name() override { return "car"; }
    std::string family() override { return "list"; }
private:
    std::shared_ptr<list<s_expression>> s_exp{};
};

class cdr: public function {
public:
    explicit cdr(std::shared_ptr<s_expression> exp) {
        if(exp->get_indicator() != "list" && exp->get_indicator() != "tuple") {
            throw std::runtime_error("wrong syntax, cdr can only get list.");
        }
        s_exp = static_pointer_cast<list<s_expression>>(exp);
    }
    std::shared_ptr<s_expression> execute() override;
    std::string return_type() override { return "list"; }
    std::string name() override { return "cdr"; }
    std::string family() override { return "list"; }
private:
    std::shared_ptr<list<s_expression>> s_exp;
};

class cons: public function {
public:
    cons(std::shared_ptr<s_expression> l, std::shared_ptr<s_expression> r): left(std::move(l)) {
        if(r->get_indicator() != "list" && r->get_indicator() != "tuple") {
            throw std::runtime_error("wrong syntax, the second argument to cons must be a list.");
        }
        right = static_pointer_cast<list<s_expression>>(r);
    }
    std::shared_ptr<s_expression> execute() override;
    std::string return_type() override { return "list"; }
    std::string name() override { return "cons"; }
    std::string family() override { return "list"; }
private:
    std::shared_ptr<s_expression> left;
    std::shared_ptr<list<s_expression>> right;
};

class is_null: public function {
public:
    explicit is_null(std::shared_ptr<s_expression> exp) {
        if(exp->get_indicator() != "list" && exp->get_indicator() != "tuple") {
            throw std::runtime_error("wrong syntax, null? is defined only for lists.");
        }
        s_exp = static_pointer_cast<list<s_expression>>(exp);
    }
    std::shared_ptr<s_expression> execute() override;
    std::string return_type() override { return "bool"; }
    std::string name() override { return "null?"; }
    std::string family() override { return "list"; }
private:
    std::shared_ptr<list<s_expression>> s_exp;
};

class add_tuple: public function {
public:
    explicit add_tuple(std::shared_ptr<s_expression> tp) {
        if(tp->get_indicator() != "tuple") {
            throw std::runtime_error("wrong syntax, null? is defined only for lists.");
        }
        tup_list = static_pointer_cast<list<integer>>(tp);
    }
    std::shared_ptr<s_expression> execute() override;
    std::string return_type() override { return "integer"; }
    std::string name() override { return "addtup"; }
    std::string family() override { return "list"; }
private:
    std::shared_ptr<list<integer>> tup_list;
};
#endif //MYSCHEME_LIST_FAMILY_H
