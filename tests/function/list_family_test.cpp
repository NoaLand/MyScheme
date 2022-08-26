#include <gtest/gtest.h>

#include "function/list_family.h"

TEST(CarTest, should_get_correct_basic_info_after_successfully_init_car_expression) {
    auto l = new list<atom>{};
    auto a1 = new atom{"a1"};
    auto a2 = new atom{"a2"};
    auto a3 = new atom{"a3"};
    l->push_back(a1);
    l->push_back(a2);
    l->push_back(a3);

    auto f = new car{l};
    ASSERT_EQ(f->name(), "car");
    ASSERT_EQ(f->return_type(), "s_expression");
    ASSERT_EQ(f->family(), "list");
}