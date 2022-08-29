#include <gtest/gtest.h>

#include "token/token.h"

TEST(TokenTest, should_get_from_buffer_when_using_putback_token) {
    std::istringstream is;
    function_context context;
    Token_stream ts{is, &context};

    Token t{'('};
    ts.put_back(t);

    const Token &token = ts.get();
    ASSERT_EQ(token.type, '(');
}