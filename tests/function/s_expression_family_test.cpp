#include <gtest/gtest.h>

#include "function/s_expression_family.h"

TEST(IsAtomTest, should_get_basic_info_when_successfully_create_is_atom_expression) {
    auto a = new atom{"a"};
    auto f = new is_atom{a};

    ASSERT_EQ(f->name(), "atom?");
    ASSERT_EQ(f->return_type(), "bool");
    ASSERT_EQ(f->family(), "s_expression");
}

TEST(IsAtomTest, should_return_true_when_input_is_an_atom) {
    auto a = new atom{"a"};

    auto f = new is_atom{a};
    auto res = f->execute();

    ASSERT_EQ(res->get_indicator(), "bool");
    ASSERT_TRUE(res->val());
}