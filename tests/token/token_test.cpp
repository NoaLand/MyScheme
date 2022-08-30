#include <gtest/gtest.h>

#include "base_test.h"
#include "preload_libs/preload_libs.h"

class BaseTokenTest: public BaseTest {
};

TEST_F(BaseTokenTest, should_get_from_buffer_when_using_putback_token) {
    Token t{'('};
    ts.put_back(t);

    const Token &token = ts.get();

    ASSERT_EQ(token.type, '(');
}

TEST_F(BaseTokenTest, should_return_token_with_left_parentheses_when_it_is_in_istream) {
    is.str("(\n");

    const Token &token = ts.get();

    ASSERT_EQ(token.type, '(');
}

TEST_F(BaseTokenTest, should_return_token_with_N_type_when_getting_an_integer_123) {
    is.str("123\n");

    const Token &token = ts.get();

    ASSERT_EQ(token.type, 'N');
    ASSERT_EQ(token.integer_value, 123);
}

TEST_F(BaseTokenTest, should_return_A_type_when_getting_input_is_123ABC){
    is.str("123ABC\n");

    const Token &token = ts.get();

    ASSERT_EQ(token.type, 'A');
    ASSERT_EQ(token.value, "123ABC");
}

TEST_F(BaseTokenTest, should_return_D_type_when_getting_input_is_define) {
    is.str("define\n");

    const Token &token = ts.get();

    ASSERT_EQ(token.type, 'D');
    ASSERT_EQ(token.value, "");
}

TEST_F(BaseTokenTest, should_return_L_type_when_getting_input_is_lambda) {
    is.str("lambda\n");

    const Token &token = ts.get();

    ASSERT_EQ(token.type, 'L');
    ASSERT_EQ(token.value, "");
}

class PrimitiveAndFuncTokenTest: public BaseTest,
                                 public testing::WithParamInterface<std::string> {};

INSTANTIATE_TEST_SUITE_P(PreloadFunc,
                         PrimitiveAndFuncTokenTest,
                         testing::Values("quote", "car", "cdr", "cons", "null?", "addtup", "atom?", "eq?", "number?",
                                         "cond", "or?","and?", "zero?", "add1", "sub1", "lat?", "length", "member?",
                                         "rember", "pick", "rempick", "+", "-", "*", "/", ">", "<", "=", "^"));

TEST_P(PrimitiveAndFuncTokenTest, should_return_F_type_when_token_is_stored) {
    preload_libs(context);
    std::string func_name = GetParam();
    is.str(func_name + "\n");

    const Token &token = ts.get();

    ASSERT_EQ(token.type, 'F');
    ASSERT_EQ(token.value, func_name);
}

class BooleanTokenTest: public BaseTest,
                        public testing::WithParamInterface<std::string> {};

INSTANTIATE_TEST_SUITE_P(BooleanKeyword,
                         BooleanTokenTest,
                         testing::Values("#t", "else", "#f"));

TEST_P(BooleanTokenTest, should_return_B_type_when_token_is_stored) {
    preload_libs(context);
    std::string func_name = GetParam();
    is.str(func_name + "\n");

    const Token &token = ts.get();

    ASSERT_EQ(token.type, 'B');
    ASSERT_EQ(token.value, func_name);
}
