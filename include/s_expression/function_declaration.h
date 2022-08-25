#ifndef MYSCHEME_FUNCTION_DECLARATION_H
#define MYSCHEME_FUNCTION_DECLARATION_H
#include <string>
#include <utility>
#include <iostream>
#include <vector>
#include <stack>

#include "list.h"
#include "params.h"

class function_declaration: public s_expression {
public:
    function_declaration(std::string n, list<param>* p, std::string b): name(std::move(n)), params(p), body(std::move(b)) {}
    std::string get_name() { return name; }
    list<param>* get_params() { return params; }
    std::string get_body() { return body; }
    std::string get_value() override;
    std::string get_indicator() override { return indicator; }
    void print(std::ostream& os) override;
private:
    std::string indicator{"customized_function"};
    std::string name;
    list<param>* params;
    std::string body;
};

class function_context {
public:
    void store(function_declaration* func);
    bool is_in(const std::string& name, bool load_to_buffer = false);
    std::string instantiate(list<s_expression>* p);
private:
    std::vector<function_declaration*> func_list{};
    std::stack<function_declaration*> buffer;
};

#endif //MYSCHEME_FUNCTION_DECLARATION_H
