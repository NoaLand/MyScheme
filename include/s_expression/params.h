#ifndef MYSCHEME_PARAMS_H
#define MYSCHEME_PARAMS_H
#include <string>
#include <utility>
#include <iostream>

#include "s_expression.h"

class param: public s_expression {
public:
    param() = default;
    explicit param(std::string v): value(std::move(v)) {}

    std::string get_value() noexcept override;
    std::string get_indicator() noexcept override { return indicator; }
    void print(std::ostream& os) noexcept override;
private:
    std::string indicator{"param"};
    std::string value;
};
#endif //MYSCHEME_PARAMS_H
