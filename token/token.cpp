#include "token.h"

#include <utility>

const char separator = 'S';

Token Token_stream::get() {
    if(full) {
        full = false;
        return buffer;
    }

    char ch;
    is >> ch;

    switch(ch) {
        case '(': case ')':
            return {ch};
        case ' ': case '\n':
            return {separator};
        default: {
            std::string s;
            s += ch;
            while(is.get(ch)) {
                if(s == "car" || s == "cdr" || s == "cons" || s == "null?") {
                    return {'F', s};
                }
                if(s == "atom?" || s == "eq?") {
                    return {'F', s};
                }
                if(context->is_in(s)) {
                    return {'F', s};
                }
                if(s == "define") {
                    return {'D'};
                }
                if(s == "lambda") {
                    return {'L'};
                }
                if (ch == ')') {
                    is.putback(ch);
                    return {'A', s};
                }
                if (ch == ' ' || ch == '\n') return {'A', s};
                s += ch;
            }

            return {'A', s};
        }
    }
}

std::istream& Token_stream::get_istream() {
    return is;
}

void Token_stream::put_back(Token t) {
    if(full) {
        throw std::runtime_error("buffer is full!!!");
    }

    full = true;
    buffer = std::move(t);
}

void Token_stream::put_back(std::string r) {
    for(int index = r.size() - 1; index >= 0; --index) {
        is.putback(r[index]);
    }
}
