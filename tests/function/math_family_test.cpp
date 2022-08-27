#include <gtest/gtest.h>

#include "function/math_family.h"

TEST(SelfAddTest, should_get_correct_basic_info_when_successfully_create_self_add_expression) {
    auto i = new integer{1};
    auto f = new self_add{i};

    ASSERT_EQ(f->name(), "add1");
    ASSERT_EQ(f->return_type(), "integer");
    ASSERT_EQ(f->family(), "math");
}

TEST(SelfAddTest, should_return_2_when_self_add_get_1_as_input) {
    auto i = new integer{1};

    auto f = new self_add{i};
    auto res = f->execute();

    ASSERT_EQ(res->get_indicator(), "integer");
    ASSERT_EQ(res->val(), 2);
}

TEST(SelfAddTest, should_return_101_when_self_add_get_100_as_input) {
    auto i = new integer{100};

    auto f = new self_add{i};
    auto res = f->execute();

    ASSERT_EQ(res->get_indicator(), "integer");
    ASSERT_EQ(res->val(), 101);
}

TEST(SelfAddTest, should_throw_exception_when_param_passing_is_not_integer) {
    auto a = new atom{"wrong_type_input"};

    ASSERT_ANY_THROW(new self_add{a});
}