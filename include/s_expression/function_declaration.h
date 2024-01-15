#ifndef MYSCHEME_FUNCTION_DECLARATION_H
#define MYSCHEME_FUNCTION_DECLARATION_H
#include <string>
#include <utility>
#include <memory>

#include "core/token.h"
#include "list.h"
#include "params.h"

class function_declaration: public s_expression {
public:
    function_declaration() = default;
    function_declaration(std::string n, std::shared_ptr<list<param>> p, std::vector<Token> b): name(std::move(n)), params(std::move(p)), body(std::move(b)) {}

    std::string get_name() { return name; }
    std::shared_ptr<list<param>> get_params() { return params; }
    std::vector<Token> get_body() { return body; }
    std::string get_value() override;
    std::string get_indicator() override { return indicator; }
    void print(std::ostream& os) override;
private:
    std::string indicator{"customized_function"};
    std::string name;
    std::shared_ptr<list<param>> params{};
    std::vector<Token> body;
};

#endif //MYSCHEME_FUNCTION_DECLARATION_H
