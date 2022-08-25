#ifndef MYSCHEME_OTHERS_H
#define MYSCHEME_OTHERS_H

#include <utility>

#include "function.h"
#include "../token/token.h"
#include "../token/s_expression/atom.h"

class quote: public function {
public:
    explicit quote(Token any): exp(std::move(any)) {}
    s_expression* execute() override;
    std::string return_type() override { return "atom"; }
    std::string name() override { return "quote"; }
    std::string family() override { return "other"; }
private:
    Token exp;
};

#endif //MYSCHEME_OTHERS_H
