#ifndef MYSCHEME_TOKEN_H
#define MYSCHEME_TOKEN_H

#include <string>
#include <vector>

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

std::string serialize_token_list(const std::vector<Token>& token_list);
#endif //MYSCHEME_TOKEN_H
