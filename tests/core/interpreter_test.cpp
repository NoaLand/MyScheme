#include "base_test.h"

#include "core/interpreter.h"

class InterpreterTest: public BaseTest {
protected:
    interpreter inter{context, ts};
};

TEST_F(InterpreterTest, should_get_one_param_successfully_when_passing_one_param_as_input) {
    is.str("(l)\n");

    auto params = inter.collect_params();

    ASSERT_EQ(params->size_of(), 1);
    ASSERT_EQ(params->get(0)->get_value(), "l");
}

TEST_F(InterpreterTest, should_get_params_successfully_when_passing_more_than_one_param) {
    is.str("(new old l)\n");

    auto params = inter.collect_params();

    ASSERT_EQ(params->size_of(), 3);
    ASSERT_EQ(params->get(0)->get_value(), "new");
    ASSERT_EQ(params->get(1)->get_value(), "old");
    ASSERT_EQ(params->get(2)->get_value(), "l");
}

TEST_F(InterpreterTest, should_throw_exception_when_the_first_token_is_not_left_parentheses) {
    is.str("wrong (new old l)\n");

    ASSERT_ANY_THROW(inter.collect_params());
}

TEST_F(InterpreterTest, should_throw_exception_when_params_type_are_not_list_of_atom) {
    is.str("(cdr (wrong new old l))\n");

    ASSERT_ANY_THROW(inter.collect_params());
}

TEST_F(InterpreterTest, should_get_function_body_successfully_when_passing_correct_syntax_body) {
    is.str("(n m)\n");
    auto params = inter.collect_params();

    is.str("(cond ((sero? m) n) (else (edd1 (p+ n (zub1 m))))))\n");
    auto body = inter.get_func_body(params);

    ASSERT_EQ(body, "(cond ( ( sero? $m$ ) $n$ ) ( else ( edd1 ( p+ $n$ ( zub1 $m$ ) ) ) ) ) ");
}

TEST_F(InterpreterTest, should_get_function_body_successfully_when_function_body_has_integer) {
    is.str("(n m)\n");
    auto params = inter.collect_params();

    is.str("(cond ((zero? m) 1) (else (* n (^ n (sub1 m)))))))\n");
    auto body = inter.get_func_body(params);

    ASSERT_EQ(body, "(cond ( ( zero? $m$ ) 1 ) ( else ( * $n$ ( ^ $n$ ( sub1 $m$ ) ) ) ) ) ");
}

TEST_F(InterpreterTest, should_throw_exception_when_parsing_body_is_not_start_with_left_parentheses) {
    is.str("(n m)\n");
    auto params = inter.collect_params();

    is.str("error function body\n");

    ASSERT_ANY_THROW(inter.get_func_body(params));
}

TEST_F(InterpreterTest, should_throw_exception_when_parsing_body_is_not_start_with_right_parentheses) {
    is.str("(n m)\n");
    auto params = inter.collect_params();

    is.str("(error function) body\n");

    ASSERT_ANY_THROW(inter.get_func_body(params));
}

TEST_F(InterpreterTest, should_successfully_define_function_when_input_function_format_is_correct_in_syntax) {
    is.str("define one? (lambda (n) (= n 1)))\n");

    auto is_one = inter.function_define();

    ASSERT_EQ(is_one->get_name(), "one?");
    ASSERT_EQ(is_one->get_indicator(), "customized_function");
    ASSERT_TRUE(context.is_in("one?"));
}

TEST_F(InterpreterTest, should_throw_exception_when_function_name_is_not_in_correct_type) {
    is.str("define (wrong func name) (lambda (n) (= n 1)))\n");

    ASSERT_ANY_THROW(inter.function_define());
}

TEST_F(InterpreterTest, should_throw_exception_when_function_define_has_not_lambda) {
    is.str("define one? ((n) (= n 1)))\n");

    ASSERT_ANY_THROW(inter.function_define());
}

TEST_F(InterpreterTest, should_construct_atom_when_getting_is_buf_has_atom) {
    is.str("123abc\n");

    auto a = inter.construct_from_token();

    ASSERT_EQ(a->get_indicator(), "atom");
    ASSERT_EQ(a->get_value(), "123abc");
}

TEST_F(InterpreterTest, should_construct_true_when_getting_is_buf_has_is_true) {
    is.str("#t\n");
    auto t = inter.construct_from_token();

    ASSERT_EQ(t->get_indicator(), "bool");
    ASSERT_EQ(dynamic_cast<boolean*>(t)->get_value(), "#t");
    ASSERT_TRUE(dynamic_cast<boolean*>(t)->val());
}

TEST_F(InterpreterTest, should_construct_true_when_getting_is_buf_has_is_else) {
    is.str("else\n");
    auto t = inter.construct_from_token();

    ASSERT_EQ(t->get_indicator(), "bool");
    ASSERT_EQ(dynamic_cast<boolean*>(t)->get_value(), "#t");
    ASSERT_TRUE(dynamic_cast<boolean*>(t)->val());
}

TEST_F(InterpreterTest, should_construct_false_when_getting_is_buf_has_is_false) {
    is.str("#f\n");
    auto t = inter.construct_from_token();

    ASSERT_EQ(t->get_indicator(), "bool");
    ASSERT_EQ(dynamic_cast<boolean*>(t)->get_value(), "#f");
    ASSERT_FALSE(dynamic_cast<boolean*>(t)->val());
}

TEST_F(InterpreterTest, should_construct_integer_10_when_getting_is_buf_has_10) {
    is.str("10\n");
    auto t = inter.construct_from_token();

    ASSERT_EQ(t->get_indicator(), "integer");
    ASSERT_EQ(dynamic_cast<integer*>(t)->get_value(), "10");
    ASSERT_EQ(dynamic_cast<integer*>(t)->val(), 10);
}
