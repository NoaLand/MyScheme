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