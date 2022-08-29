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

TEST(TokenTest, should_throw_exception_when_putback_token_twice_at_the_same_time) {
    std::istringstream is;
    function_context context;
    Token_stream ts{is, &context};

    Token t{'('};
    ts.put_back(t);

    ASSERT_ANY_THROW(ts.put_back(t));
}

TEST(TokenTest, should_return_token_with_N_type_when_getting_an_integer_123) {
    std::istringstream is;
    is.str("123\n");
    function_context context;
    Token_stream ts{is, &context};

    const Token &token = ts.get();
    ASSERT_EQ(token.type, 'N');
    ASSERT_EQ(token.integer_value, 123);
}