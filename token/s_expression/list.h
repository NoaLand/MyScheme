#ifndef MYSCHEME_LIST_H
#define MYSCHEME_LIST_H

#include <vector>

#include "../token.h"
#include "s_expression.h"

class list: public s_expression{
public:
    list() = default;
    std::unique_ptr<s_expression>& get(int index);
    size_t size_of() {return l.size(); }
    bool empty() { return l.empty(); }
    bool has_value(std::string);
    std::string get_value() override;
    std::string get_indicator() override { return indicator; }
    void print(std::ostream& os) override;
    std::vector<std::unique_ptr<s_expression>>& get_iterator() { return l; }
    void push_back(std::unique_ptr<s_expression> s_exp);
private:
    std::string indicator{"tuple"};
    std::vector<std::unique_ptr<s_expression>> l{};
};
#endif //MYSCHEME_LIST_H
