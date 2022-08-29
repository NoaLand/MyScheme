#include <gtest/gtest.h>

#include "function/nor_logic_family.h"

TEST(OrLogicTest, should_get_correct_basic_info_when_successfully_create_or_logic_expression) {
    auto l = new boolean{true};
    auto r = new boolean{false};

    auto f = new or_logic{l, r};

    ASSERT_EQ(f->name(), "or?");
    ASSERT_EQ(f->return_type(), "bool");
    ASSERT_EQ(f->family(), "nor_logic");
}

TEST(OrLogicTest, should_return_true_when_r_or_l_is_true) {
    auto l = new boolean{true};
    auto r = new boolean{false};

    auto f = new or_logic{l, r};
    auto res = f->execute();

    ASSERT_EQ(res->get_indicator(), "bool");
    ASSERT_EQ(res->val(), true);
}