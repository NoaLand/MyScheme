#ifndef MYSCHEME_NOR_LOGIC_FAMILY_H
#define MYSCHEME_NOR_LOGIC_FAMILY_H

#include "function.h"
#include "s_expression/atom.h"

class or_logic: public function {
public:
    or_logic(s_expression* l, s_expression* r) {
        if(l->get_indicator() != "bool" || r->get_indicator() != "bool") {
            throw std::runtime_error("wrong syntax: or need take bool as input");
        }
        left = dynamic_cast<boolean*>(l);
        right = dynamic_cast<boolean*>(r);
    }
    boolean* execute() override;
    std::string return_type() override { return "bool"; }
    std::string name() override { return "or?"; }
    std::string family() override { return "nor_logic"; }

    ~or_logic() override {
        delete execute_res;
    }
private:
    boolean* left;
    boolean* right;

    boolean* execute_res{};
};


class and_logic: public function {
public:
    and_logic(s_expression* l, s_expression* r) {
        if(l->get_indicator() != "bool" || r->get_indicator() != "bool") {
            throw std::runtime_error("wrong syntax: function and need take bool as input");
        }
        left = dynamic_cast<boolean*>(l);
        right = dynamic_cast<boolean*>(r);
    }
    boolean* execute() override;
    std::string return_type() override { return "bool"; }
    std::string name() override { return "and?"; }
    std::string family() override { return "nor_logic"; }
private:
    boolean* left;
    boolean* right;
};
#endif //MYSCHEME_NOR_LOGIC_FAMILY_H
