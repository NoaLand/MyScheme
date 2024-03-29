#ifndef MYSCHEME_TOKEN_STREAM_H
#define MYSCHEME_TOKEN_STREAM_H

#include <queue>

#include "core/token.h"
#include "core/function/function_context.h"

// for Token_stream, our compiler will load Scheme code as istream, I gonna wrap it and refer this as the wrapper of istream, which means, it will have buffer, and istream inside of it
class Token_stream {
public:
    Token_stream(std::istream& i, std::ostream& o, function_context& c): is(i), os(o), context(c) {}
    Token get();
    std::istream& get_istream();
    std::ostream& get_ostream();
    function_context& get_context();
    void put_back(const Token&);

    void push_back(const std::vector<Token> &token_list) noexcept;

private:
    std::deque<Token> buffer_queue;
    std::istream& is;
    std::ostream& os;
    function_context& context;
};

#endif //MYSCHEME_TOKEN_STREAM_H
