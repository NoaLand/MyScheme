#ifndef MYSCHEME_SCHEME_LIST_H
#define MYSCHEME_SCHEME_LIST_H

#include <vector>

#include "token.h"

class scheme_list {
public:
    std::vector<Token> list;
};

std::ostream& operator<<(std::ostream& os, const scheme_list& sl);

#endif //MYSCHEME_SCHEME_LIST_H
