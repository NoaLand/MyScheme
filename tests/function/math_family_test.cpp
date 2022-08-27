#include <gtest/gtest.h>

#include "function/math_family.h"

TEST(SelfAddTest, should_get_correct_basic_info_when_successfully_create_self_add_expression) {
    auto i = new integer{1};
    auto f = new self_add{i};

    ASSERT_EQ(f->name(), "add1");
    ASSERT_EQ(f->return_type(), "integer");
    ASSERT_EQ(f->family(), "math");
}