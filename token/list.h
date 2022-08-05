#ifndef MYSCHEME_LIST_H
#define MYSCHEME_LIST_H

#include <vector>

#include "token.h"

class list {
public:
    std::vector<Token> list;
};

std::ostream& operator<<(std::ostream& os, const list& sl);

#endif //MYSCHEME_LIST_H
