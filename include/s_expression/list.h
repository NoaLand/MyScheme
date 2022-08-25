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
    T* get(const int& index);
    size_t size_of() {return l.size(); }
    bool empty() { return l.empty(); }
    bool has_value(const std::string& value);
    std::string get_value() override;
    std::string get_indicator() override { return indicator; }
    void print(std::ostream& os) override;
    std::vector<T*> get_iterator() { return l; }
    void push_back(T* s_exp);
private:
    std::string indicator{"tuple"};
    std::vector<T*> l{};
};

template<typename T>
requires std::derived_from<T, s_expression>
T* list<T>::get(const int& index) {
    return l.at(index);
}

template<typename T>
requires std::derived_from<T, s_expression>
bool list<T>::has_value(const std::string& value) {
    for(const auto& element : l) {
        if(element->get_value() == value) {
            return true;
        }
    }

    return false;
}

template<typename T>
requires std::derived_from<T, s_expression>
std::string list<T>::get_value() {
    std::string res = "( ";
    for (auto atom : l) {
        res += atom->get_value();
        res += " ";
    }
    res += ")";

    return res;
}

template<typename T>
requires std::derived_from<T, s_expression>
void list<T>::print(std::ostream &os) {
    os << get_indicator() << ": " << get_value() << std::endl;
}

template<typename T>
requires std::derived_from<T, s_expression>
void list<T>::push_back(T* s_exp) {
    if(s_exp->get_indicator() != "integer" && indicator == "tuple") {
        indicator = "list";
    }
    l.push_back(s_exp);
}

#endif //MYSCHEME_LIST_H
