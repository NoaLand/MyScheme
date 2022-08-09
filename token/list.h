#ifndef MYSCHEME_LIST_H
#define MYSCHEME_LIST_H

#include <vector>

#include "token.h"
#include "s_expression.h"

class list: public s_expression{
public:
    std::string get_value() override;
    void push_back(s_expression* s_exp);
private:
    std::string indicator{"list"};
    std::vector<s_expression*> l{};
};

std::ostream& operator<<(std::ostream& os, list l);

#endif //MYSCHEME_LIST_H
