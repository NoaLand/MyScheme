#ifndef MYSCHEME_LIST_H
#define MYSCHEME_LIST_H

#include <concepts>
#include <vector>

#include "s_expression.h"

template <typename T>
requires std::derived_from<T, s_expression>
class list: public s_expression{
public:
    list() = default;
    list(const std::vector<s_expression*>::iterator& begin, const std::vector<s_expression*>::iterator& end) {
        l = {begin, end};
    }
    T* get(const int& index) {
        return l.at(index);
    }
    size_t size_of() {
        return l.size();
    }
    bool empty() {
        return l.empty();
    }
    bool has_value(const std::string& value) {
        return std::any_of(l.begin(),
                           l.end(),
                           [&value](auto e){ return e->get_value() == value; });
    }
    std::string get_value() override {
        std::string res = "( ";
        for (auto atom : l) {
            res += atom->get_value();
            res += " ";
        }
        res += ")";

        return res;
    }
    std::string get_indicator() override {
        return std::all_of(l.begin(),
                           l.end(),
                           [](auto e) { return e->get_indicator() == "integer"; }) ? "tuple" : "list";
    }
    void print(std::ostream& os) override {
        os << get_indicator() << ": " << get_value() << std::endl;
    }
    std::vector<T*> get_iterator() {
        return l;
    }
    void push_back(T* s_exp) {
        l.push_back(s_exp);
    }
private:
    std::string indicator;
    std::vector<T*> l{};
};
#endif //MYSCHEME_LIST_H
