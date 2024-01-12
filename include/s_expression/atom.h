#ifndef MYSCHEME_ATOM_H
#define MYSCHEME_ATOM_H
#include <string>
#include <utility>
#include <iostream>

#include "s_expression.h"

class atom: public s_expression {
public:
    atom() = default;
    explicit atom(std::string v): value(std::move(v)) {}
    std::string get_value() override;
    std::string get_indicator() override { return indicator; }
    void print(std::ostream& os) override;
private:
    std::string indicator{"atom"};
    std::string value;
};

class boolean: public s_expression {
public:
    boolean() = default;
    explicit boolean(bool b) {
        value = b ? "#t" : "#f";
    }
    explicit boolean(const std::string& b) {
        if(b != "#t" && b != "else" && b != "#f") {
            throw std::runtime_error("wrong syntax: boolean can only take #t/#f/else!");
        }

        value = b;
    }
    explicit boolean(const char* b) : boolean(std::string(b)) {}

    std::string get_value() override;
    std::string get_indicator() override { return indicator; }
    void print(std::ostream& os) override;
    bool val();
private:
    std::string indicator{"bool"};
    std::string value;
};

class integer: public s_expression {
public:
    integer() = default;
    explicit integer(int i): value(i) {}
    std::string get_value() override;
    std::string get_indicator() override { return indicator; }
    void print(std::ostream& os) override;
    int val() const;
private:
    std::string indicator{"integer"};
    int value{0};
};
#endif //MYSCHEME_ATOM_H
