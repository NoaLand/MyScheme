#ifndef MYSCHEME_OTHERS_H
#define MYSCHEME_OTHERS_H

#include <utility>

#include "function.h"
#include "s_expression/atom.h"

class quote: public function {
public:
    explicit quote(s_expression* any): exp(any) {}
    atom* execute() override;
    std::string return_type() override { return "atom"; }
    std::string name() override { return "quote"; }
    std::string family() override { return "other"; }
private:
    s_expression* exp;
};

#endif //MYSCHEME_OTHERS_H
