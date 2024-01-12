#include <gtest/gtest.h>

#include "function/math_family.h"

TEST(SelfAddTest, should_get_correct_basic_info_when_successfully_create_self_add_expression) {
    auto i = integer{1};
    auto f = self_add{&i};

    ASSERT_EQ(f.name(), "add1");
    ASSERT_EQ(f.return_type(), "integer");
    ASSERT_EQ(f.family(), "math");
}

TEST(SelfAddTest, should_return_2_when_self_add_get_1_as_input) {
    auto i = integer{1};

    auto f = self_add{&i};
    auto res = f.execute();

    ASSERT_EQ(res->get_indicator(), "integer");
    ASSERT_EQ(res->val(), 2);
}

TEST(SelfAddTest, should_return_101_when_self_add_get_100_as_input) {
    auto i = integer{100};

    auto f = self_add{&i};
    auto res = f.execute();

    ASSERT_EQ(res->get_indicator(), "integer");
    ASSERT_EQ(res->val(), 101);
}

TEST(SelfAddTest, should_throw_exception_when_param_passing_is_not_integer) {
    auto a = atom{"wrong_type_input"};

    ASSERT_ANY_THROW(self_add{&a});
}

TEST(SelfSubTest, should_get_correct_basic_info_when_successfully_create_self_sub_expression) {
    auto i = integer{1};
    auto f = self_sub{&i};

    ASSERT_EQ(f.name(), "sub1");
    ASSERT_EQ(f.return_type(), "integer");
    ASSERT_EQ(f.family(), "math");
}

TEST(SelfSubTest, should_return_1_when_self_sub_get_2_as_input) {
    auto i = integer{2};

    auto f = self_sub{&i};
    auto res = f.execute();

    ASSERT_EQ(res->get_indicator(), "integer");
    ASSERT_EQ(res->val(), 1);
}

TEST(SelfSubTest, should_return_100_when_self_sub_get_101_as_input) {
    auto i = integer{101};

    auto f = self_sub{&i};
    auto res = f.execute();

    ASSERT_EQ(res->get_indicator(), "integer");
    ASSERT_EQ(res->val(), 100);
}

TEST(SelfSubTest, should_throw_exception_when_param_passing_is_not_integer) {
    auto a = atom{"wrong_type_input"};

    ASSERT_ANY_THROW(self_sub{&a});
}

TEST(IsZeroTest, should_get_correct_basic_info_when_successfully_create_is_zero_expression) {
    auto i = integer{1};
    auto f = is_zero{&i};

    ASSERT_EQ(f.name(), "zero?");
    ASSERT_EQ(f.return_type(), "bool");
    ASSERT_EQ(f.family(), "math");
}

TEST(IsZeroTest, should_return_true_when_function_get_0) {
    auto i = integer{0};

    auto f = is_zero{&i};
    auto res = f.execute();

    ASSERT_EQ(res->get_indicator(), "bool");
    ASSERT_TRUE(res->val());
}

TEST(IsZeroTest, should_return_false_when_function_get_non_zero_as_input) {
    auto i = integer{100};

    auto f = is_zero{&i};
    auto res = f.execute();

    ASSERT_EQ(res->get_indicator(), "bool");
    ASSERT_FALSE(res->val());
}

TEST(IsZeroTest, should_throw_exception_when_function_get_input_type_is_wrong) {
    auto a = atom{"wrong_type_input"};

    ASSERT_ANY_THROW(is_zero{&a});
}