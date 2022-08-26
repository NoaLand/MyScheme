#include <gtest/gtest.h>

#include "s_expression/atom.h"

TEST(AtomTest, should_get_value_successfully_after_create_atom) {
    auto a = new atom{"value_of_atom"};
    ASSERT_EQ(a->get_value(), "value_of_atom");
    ASSERT_EQ(a->get_indicator(), "atom");

    std::ostringstream buf;
    a->print(buf);
    ASSERT_EQ(buf.str(), "atom: value_of_atom\n");
}

TEST(BooleanTest, should_set_true_successfully_when_pass_bool_true) {
    auto b = new boolean{true};
    ASSERT_EQ(b->val(), true);
    ASSERT_EQ(b->get_value(), "#t");
    ASSERT_EQ(b->get_indicator(), "bool");

    std::ostringstream buf;
    b->print(buf);
    ASSERT_EQ(buf.str(), "bool: #t\n");
}

TEST(BooleanTest, should_set_false_successfully_when_pass_bool_false) {
    auto b = new boolean{false};

    ASSERT_EQ(b->val(), false);
    ASSERT_EQ(b->get_value(), "#f");
    ASSERT_EQ(b->get_indicator(), "bool");

    std::ostringstream buf;
    b->print(buf);
    ASSERT_EQ(buf.str(), "bool: #f\n");
}

TEST(BooleanTest, should_set_true_when_pass_string_t) {
    const std::string true_string = "#t";
    auto b = new boolean{true_string};

    ASSERT_EQ(b->val(), true);
    ASSERT_EQ(b->get_value(), "#t");
    ASSERT_EQ(b->get_indicator(), "bool");
}

TEST(BooleanTest, should_set_true_when_pass_else) {
    const std::string else_string = "else";
    auto b = new boolean{else_string};

    ASSERT_EQ(b->val(), true);
    ASSERT_EQ(b->get_value(), "#t");
    ASSERT_EQ(b->get_indicator(), "bool");
}

TEST(BooleanTest, should_set_false_when_pass_string_f) {
    const std::string false_string = "#f";
    auto b = new boolean{false_string};

    ASSERT_EQ(b->val(), false);
    ASSERT_EQ(b->get_value(), "#f");
    ASSERT_EQ(b->get_indicator(), "bool");
}

TEST(BooleanTest, should_throw_exception_when_input_is_not_t_or_else_or_f) {
    const std::string err_string = "err";
    ASSERT_ANY_THROW(new boolean{err_string});
}

TEST(IntegerTest, should_set_10_to_integer_when_passing_10) {
    auto i = new integer{10};
    ASSERT_EQ(i->val(), 10);
    ASSERT_EQ(i->get_value(), "10");
    ASSERT_EQ(i->get_indicator(), "integer");

    std::ostringstream buf;
    i->print(buf);
    ASSERT_EQ(buf.str(), "integer: 10\n");
}