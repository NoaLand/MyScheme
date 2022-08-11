#ifndef MYSCHEME_TOKEN_H
#define MYSCHEME_TOKEN_H

#include <string>
#include <utility>
#include <iostream>
#include "s_expression/function_declaration.h"

// for Tokens, every single word in Scheme can be a token, which means. it can be every single element it has, so token can represent for its type, value in string
// type means the basic type for token, such as: atom -> A, () -> (), and car -> F
class Token {
public:
    Token(char t): type(t) {}
    Token(char t, std::string v): type(t), value(std::move(v)) {}
    char type;
    std::string value;
};

// for Token_stream, our compiler will load Scheme code as istream, I gonna wrap it and refer this as the wrapper of istream, which means, it will have buffer, and istream inside of it
class Token_stream {
public:
    Token_stream(std::istream& i, function_context* c): is(i), context(c), full(false), buffer(0) {}
    Token get();
    std::istream& get_istream();
    void put_back(Token);
    void put_back(std::string);
private:
    bool full;
    Token buffer;
    std::istream& is;
    function_context* context;
};

#endif //MYSCHEME_TOKEN_H
