#ifndef MYSCHEME_LIST_H
#define MYSCHEME_LIST_H

#include <vector>

#include "../token.h"
#include "s_expression.h"

class list: public s_expression{
public:
    list() = default;
    list(list const &copy) { l = copy.l; }
    s_expression* get(int index);
    size_t size_of() {return l.size(); }
    bool empty() { return l.empty(); }
    std::string get_value() override;
    std::string get_indicator() override { return indicator; }
    void print(std::ostream& os) override;
    void push_back(s_expression* s_exp);
private:
    std::string indicator{"list"};
    std::vector<s_expression*> l{};
};
#endif //MYSCHEME_LIST_H