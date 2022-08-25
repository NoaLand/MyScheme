#include <gtest/gtest.h>

#include "s_expression/atom.h"

TEST(AtomTest, should_get_value_successfully_after_create_atom) {
    auto a = new atom{"value_of_atom"};
    const std::string& atom_value = a->get_value();
    const std::string& atom_indicator = a->get_indicator();

    ASSERT_EQ(atom_value, "value_of_atom");
    ASSERT_EQ(atom_indicator, "atom");
}

TEST(BooleanTest, should_set_true_successfully_when_pass_bool_true) {
    auto b = new boolean{true};
    bool val = b->val();
    const std::string& boolean_value = b->get_value();
    const std::string& boolean_indicator = b->get_indicator();

    ASSERT_EQ(val, true);
    ASSERT_EQ(boolean_value, "#t");
    ASSERT_EQ(boolean_indicator, "bool");
}

TEST(BooleanTest, should_set_false_successfully_when_pass_bool_false) {
    auto b = new boolean{false};
    bool val = b->val();
    const std::string& boolean_value = b->get_value();
    const std::string& boolean_indicator = b->get_indicator();

    ASSERT_EQ(val, false);
    ASSERT_EQ(boolean_value, "#f");
    ASSERT_EQ(boolean_indicator, "bool");
}

TEST(BooleanTest, should_set_true_when_pass_string_t) {
    const std::string true_string = "#t";
    auto b = new boolean{true_string};
    bool val = b->val();
    const std::string& boolean_value = b->get_value();
    const std::string& boolean_indicator = b->get_indicator();

    ASSERT_EQ(val, true);
    ASSERT_EQ(boolean_value, "#t");
    ASSERT_EQ(boolean_indicator, "bool");
}

TEST(BooleanTest, should_set_true_when_pass_else) {
    const std::string else_string = "else";
    auto b = new boolean{else_string};
    bool val = b->val();
    const std::string& boolean_value = b->get_value();
    const std::string& boolean_indicator = b->get_indicator();

    ASSERT_EQ(val, true);
    ASSERT_EQ(boolean_value, "#t");
    ASSERT_EQ(boolean_indicator, "bool");
}

TEST(BooleanTest, should_set_false_when_pass_string_f) {
    const std::string false_string = "#f";
    auto b = new boolean{false_string};
    bool val = b->val();
    const std::string& boolean_value = b->get_value();
    const std::string& boolean_indicator = b->get_indicator();

    ASSERT_EQ(val, false);
    ASSERT_EQ(boolean_value, "#f");
    ASSERT_EQ(boolean_indicator, "bool");
}

TEST(IntegerTest, should_set_10_to_integer_when_passing_10) {
    auto i = new integer{10};
    auto val = i->val();
    const std::string& int_to_string = i->get_value();
    const std::string& int_indicator = i->get_indicator();

    ASSERT_EQ(val, 10);
    ASSERT_EQ(int_to_string, "10");
    ASSERT_EQ(int_indicator, "integer");
}