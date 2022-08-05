#ifndef MYSCHEME_LIST_H
#define MYSCHEME_LIST_H

#include <vector>

#include "token.h"
#include "s_expression.h"

class list: public virtual s_expression{
public:
    std::string get_value();
    void push_back(Token token);
private:
    std::string indicator;
    std::vector<Token> list;
};

std::ostream& operator<<(std::ostream& os, list sl);

#endif //MYSCHEME_LIST_H
