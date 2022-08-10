#ifndef MYSCHEME_LIST_H
#define MYSCHEME_LIST_H

#include <vector>

#include "token.h"
#include "s_expression.h"

class list: public s_expression{
public:
    list() = default;
    list(list const &copy) { l = copy.l; }
    std::string car();
    std::string get_value() override;
    void print(std::ostream& os) override;
    void push_back(s_expression* s_exp);
private:
    std::string indicator{"list"};
    std::vector<s_expression*> l{};
};
#endif //MYSCHEME_LIST_H
