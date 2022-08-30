#ifndef MYSCHEME_FUNCTION_DECLARATION_H
#define MYSCHEME_FUNCTION_DECLARATION_H
#include <string>

#include "token/token.h"
#include "list.h"
#include "params.h"

class function_declaration: public s_expression {
public:
    function_declaration() = default;
    function_declaration(std::string n, list<param>* p, std::string b): name(std::move(n)), params(p), serialized_body(std::move(b)) {}

    function_declaration(std::string n, list<param>* p, std::vector<Token> b): name(std::move(n)), params(p), body(b), serialized_body(serialize_token_list(b)) {}
    
    std::string get_name() { return name; }
    list<param>* get_params() { return params; }
    std::string get_body() { return serialize_token_list(body); }
    std::string get_value() override;
    std::string get_indicator() override { return indicator; }
    void print(std::ostream& os) override;
private:
    std::string indicator{"customized_function"};
    std::string name;
    list<param>* params{};
    std::string serialized_body;
    std::vector<Token> body;
};

#endif //MYSCHEME_FUNCTION_DECLARATION_H
