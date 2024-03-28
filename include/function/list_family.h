#ifndef MYSCHEME_LIST_FAMILY_H
#define MYSCHEME_LIST_FAMILY_H

#include <numeric>
#include <utility>

#include "function.h"
#include "s_expression/atom.h"
#include "s_expression/list.h"

class car: public function {
public:
    explicit car(const std::shared_ptr<s_expression>& exp) {
        if(exp->get_indicator() != "list" && exp->get_indicator() != "tuple") {
            throw std::runtime_error("wrong syntax, car can only get list.");
        }
        s_exp = static_pointer_cast<list<s_expression>>(exp);
    }
    std::shared_ptr<s_expression> execute() override;
    std::string return_type() noexcept override { return "s_expression"; }
    std::string name() noexcept override { return "car"; }
    std::string family() noexcept override { return "list"; }
private:
    std::shared_ptr<list<s_expression>> s_exp{};
};

class cdr: public function {
public:
    explicit cdr(const std::shared_ptr<s_expression>& exp) {
        if(exp->get_indicator() != "list" && exp->get_indicator() != "tuple") {
            throw std::runtime_error("wrong syntax, cdr can only get list.");
        }
        s_exp = static_pointer_cast<list<s_expression>>(exp);
    }
    std::shared_ptr<s_expression> execute() override;
    std::string return_type() noexcept override { return "list"; }
    std::string name() noexcept override { return "cdr"; }
    std::string family() noexcept override { return "list"; }
private:
    std::shared_ptr<list<s_expression>> s_exp;
};

class cons: public function {
public:
    cons(const std::shared_ptr<s_expression>& l, const std::shared_ptr<s_expression>& r): left(l) {
        if(r->get_indicator() != "list" && r->get_indicator() != "tuple") {
            throw std::runtime_error("wrong syntax, the second argument to cons must be a list.");
        }
        right = static_pointer_cast<list<s_expression>>(r);
    }
    std::shared_ptr<s_expression> execute() override;
    std::string return_type() noexcept override { return "list"; }
    std::string name() noexcept override { return "cons"; }
    std::string family() noexcept override { return "list"; }
private:
    std::shared_ptr<s_expression> left;
    std::shared_ptr<list<s_expression>> right;
};

class is_null: public function {
public:
    explicit is_null(const std::shared_ptr<s_expression>& exp) {
        if(exp->get_indicator() != "list" && exp->get_indicator() != "tuple") {
            throw std::runtime_error("wrong syntax, null? is defined only for lists.");
        }
        s_exp = static_pointer_cast<list<s_expression>>(exp);
    }
    std::shared_ptr<s_expression> execute() override;
    std::string return_type() noexcept override { return "bool"; }
    std::string name() noexcept override { return "null?"; }
    std::string family() noexcept override { return "list"; }
private:
    std::shared_ptr<list<s_expression>> s_exp;
};

class add_tuple: public function {
public:
    explicit add_tuple(const std::shared_ptr<s_expression>& tp) {
        if(tp->get_indicator() != "tuple") {
            throw std::runtime_error("wrong syntax, null? is defined only for lists.");
        }
        tup_list = static_pointer_cast<list<integer>>(tp);
    }
    std::shared_ptr<s_expression> execute() override;
    std::string return_type() noexcept override { return "integer"; }
    std::string name() noexcept override { return "addtup"; }
    std::string family() noexcept override { return "list"; }
private:
    std::shared_ptr<list<integer>> tup_list;
};
#endif //MYSCHEME_LIST_FAMILY_H
