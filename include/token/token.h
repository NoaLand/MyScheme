#ifndef MYSCHEME_TOKEN_H
#define MYSCHEME_TOKEN_H

#include <string>
#include <utility>
#include <iostream>
#include <queue>

#include "core/function_context.h"

// for Tokens, every single word in Scheme can be a token, which means. it can be every single element it has, so token can represent for its type, value in string
// type means the basic type for token, such as: atom -> A, () -> (), and car -> F
class Token {
public:
    explicit Token(char t): type(t) {}
    Token(char t, std::string v): type(t), value(std::move(v)) {}
    Token(char t, int v): type(t), integer_value(v) {}
    char type;
    std::string value;
    int integer_value{0};
};

// for Token_stream, our compiler will load Scheme code as istream, I gonna wrap it and refer this as the wrapper of istream, which means, it will have buffer, and istream inside of it
class Token_stream {
public:
    Token_stream(std::istream& i, std::ostream& o, function_context* c): is(i), os(o), context(c) {}
    Token get();
    std::istream& get_istream();
    std::ostream& get_ostream();
    void put_back(const Token&);
    void put_back(std::string);
private:
    std::queue<Token> buffer_queue;
    std::istream& is;
    std::ostream& os;
    function_context* context;
};

std::string serialize_token_list(std::vector<Token> token_list);
#endif //MYSCHEME_TOKEN_H
