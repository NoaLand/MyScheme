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

TEST(CarTest, should_return_a1_when_car_get_a1_a2_a3_list) {
    auto l = new list<atom>{};
    auto a1 = new atom{"a1"};
    auto a2 = new atom{"a2"};
    auto a3 = new atom{"a3"};
    l->push_back(a1);
    l->push_back(a2);
    l->push_back(a3);

    auto f = new car{l};
    auto res = f->execute();

    ASSERT_EQ(res->get_indicator(), "atom");
    ASSERT_EQ(res->get_value(), "a1");
}

TEST(CarTest, should_return_a1_a2_list_when_car_get_a1_a2_list_a3_a4) {
    auto l1 = new list<atom>{};
    auto a1 = new atom{"a1"};
    auto a2 = new atom{"a2"};
    l1->push_back(a1);
    l1->push_back(a2);

    auto l2 = new list<s_expression>{};
    auto a3 = new atom{"a3"};
    auto a4 = new atom{"a4"};
    l2->push_back(l1);
    l2->push_back(a3);
    l2->push_back(a4);

    auto f = new car{l2};
    auto res = f->execute();

    ASSERT_EQ(res->get_indicator(), "list");
    ASSERT_EQ(dynamic_cast<list<atom>*>(res)->size_of(), 2);
    ASSERT_EQ(dynamic_cast<list<atom>*>(res)->get(0)->get_value(), "a1");
    ASSERT_EQ(dynamic_cast<list<atom>*>(res)->get(1)->get_value(), "a2");
}

TEST(CarTest, should_throw_exception_when_create_car_primitive_if_passing_s_expression_is_not_a_list) {
    auto err_input = new atom{"err_input"};
    ASSERT_ANY_THROW(new car{err_input});
}

TEST(CarTest, should_throw_exception_when_call_car_primitive_execute_with_empty_list) {
    auto empty_list = new list<atom>{};
    auto f = new car{empty_list};
    ASSERT_ANY_THROW(f->execute());
}