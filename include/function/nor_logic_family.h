#ifndef MYSCHEME_NOR_LOGIC_FAMILY_H
#define MYSCHEME_NOR_LOGIC_FAMILY_H

#include "function.h"
#include "s_expression/atom.h"

class or_logic: public function {
public:
    or_logic(const std::shared_ptr<s_expression>& l, const std::shared_ptr<s_expression>& r) {
        if(l->get_indicator() != "bool" || r->get_indicator() != "bool") {
            throw std::runtime_error("wrong syntax: or need take bool as input");
        }
        left = dynamic_pointer_cast<boolean>(l);
        right = dynamic_pointer_cast<boolean>(r);
    }
    std::shared_ptr<s_expression> execute() override;
    std::string return_type() noexcept override { return "bool"; }
    std::string name() noexcept override { return "or?"; }
    std::string family() noexcept override { return "nor_logic"; }
private:
    std::shared_ptr<boolean> left;
    std::shared_ptr<boolean> right;
};


class and_logic: public function {
public:
    and_logic(const std::shared_ptr<s_expression>& l, const std::shared_ptr<s_expression>& r) {
        if(l->get_indicator() != "bool" || r->get_indicator() != "bool") {
            throw std::runtime_error("wrong syntax: function and need take bool as input");
        }
        left = dynamic_pointer_cast<boolean>(l);
        right = dynamic_pointer_cast<boolean>(r);
    }
    std::shared_ptr<s_expression> execute() override;
    std::string return_type() noexcept override { return "bool"; }
    std::string name() noexcept override { return "and?"; }
    std::string family() noexcept override { return "nor_logic"; }
private:
    std::shared_ptr<boolean> left;
    std::shared_ptr<boolean> right;
};
#endif //MYSCHEME_NOR_LOGIC_FAMILY_H
