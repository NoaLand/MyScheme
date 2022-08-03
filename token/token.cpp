#include "token.h"

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
