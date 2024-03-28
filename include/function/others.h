#ifndef MYSCHEME_OTHERS_H
#define MYSCHEME_OTHERS_H

#include <utility>

#include "function.h"
#include "s_expression/atom.h"

class quote: public function {
public:
    explicit quote(std::shared_ptr<s_expression> any): exp(std::move(any)) {}
    std::shared_ptr<s_expression> execute() override;
    std::string return_type() noexcept override { return "atom"; }
    std::string name() noexcept override { return "quote"; }
    std::string family() noexcept override { return "other"; }
private:
    std::shared_ptr<s_expression> exp;
};

#endif //MYSCHEME_OTHERS_H
