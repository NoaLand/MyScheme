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