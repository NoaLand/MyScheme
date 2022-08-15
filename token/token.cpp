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

    std::string s;
    switch(ch) {
        case '(': case ')':
            return {ch};
        case ' ': case '\n':
            return {separator};
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9': {
            is.putback(ch);
            int val;
            is >> val;

            char next_char = is.get();
            if(next_char != ' ' && next_char != '\n' && next_char != ')' && next_char != 0) {
                is.putback(next_char);
                const std::string &_ = std::to_string(val);
                for(int index = _.size() - 1; index >= 1; --index) {
                    is.putback(_[index]);
                }
            } else {
                is.putback(next_char);
                return {'N', val};
            }
        }
        default: {
            s += ch;
            while(is.get(ch)) {
                if (ch == ' ' || ch == '\n' || ch == ')' || ch == '\0') {
                    is.putback(ch);
                    if(s == "car" || s == "cdr" || s == "cons" || s == "null?" || s == "addtup") {
                        return {'F', s};
                    }
                    if(s == "atom?" || s == "eq?") {
                        return {'F', s};
                    }
                    if(s == "cond") {
                        return {'F', s};
                    }
                    if(s == "or?") {
                        return {'F', s};
                    }
                    if(s == "zero?") {
                        return {'F', s};
                    }
                    if(s == "add1" || s == "sub1") {
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
                    if(s == "#t" || s == "else") {
                        return {'B' ,s};
                    }
                    if(s == "#f") {
                        return {'B', s};
                    }
                    return {'A', s};
                } else {
                    s += ch;
                }
            }
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
