#ifndef MYSCHEME_OTHERS_H
#define MYSCHEME_OTHERS_H

#include <utility>

#include "function.h"
#include "../token.h"
#include "../s_expression/atom.h"

class quote: public function {
public:
    quote(Token any): exp(std::move(any)) {}
    s_expression* execute() override;
    std::string return_type() override { return "atom"; }
    std::string name() override { return "quote"; }
private:
    Token exp;
};

#endif //MYSCHEME_OTHERS_H
