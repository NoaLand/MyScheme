#include <gtest/gtest.h>

#include "function/list_family.h"

TEST(CarTest, should_get_correct_basic_info_after_successfully_init_car_expression) {
    auto l = list<atom>{};
    auto a1 = atom{"a1"};
    auto a2 = atom{"a2"};
    auto a3 = atom{"a3"};
    l.push_back(&a1);
    l.push_back(&a2);
    l.push_back(&a3);

    auto f = car{&l};
    ASSERT_EQ(f.name(), "car");
    ASSERT_EQ(f.return_type(), "s_expression");
    ASSERT_EQ(f.family(), "list");
}

TEST(CarTest, should_return_a1_when_car_get_a1_a2_a3_list) {
    auto l = list<atom>{};
    auto a1 = atom{"a1"};
    auto a2 = atom{"a2"};
    auto a3 = atom{"a3"};
    l.push_back(&a1);
    l.push_back(&a2);
    l.push_back(&a3);

    auto f = car{&l};
    auto res = f.execute();

    ASSERT_EQ(res->get_indicator(), "atom");
    ASSERT_EQ(res->get_value(), "a1");
}

TEST(CarTest, should_return_1_when_car_get_1_2_3_tuple) {
    auto l = list<integer>{};
    auto i1 = integer{1};
    auto i2 = integer{2};
    auto i3 = integer{3};
    l.push_back(&i1);
    l.push_back(&i2);
    l.push_back(&i3);

    auto f = car{&l};
    auto res = f.execute();

    ASSERT_EQ(res->get_indicator(), "integer");
    ASSERT_EQ(dynamic_cast<integer*>(res)->val(), 1);
}

TEST(CarTest, should_return_a1_a2_list_when_car_get_a1_a2_list_a3_a4) {
    auto l1 = list<atom>{};
    auto a1 = atom{"a1"};
    auto a2 = atom{"a2"};
    l1.push_back(&a1);
    l1.push_back(&a2);

    auto l2 = list<s_expression>{};
    auto a3 = atom{"a3"};
    auto a4 = atom{"a4"};
    l2.push_back(&l1);
    l2.push_back(&a3);
    l2.push_back(&a4);

    auto f = car{&l2};
    auto res = f.execute();

    ASSERT_EQ(res->get_indicator(), "list");
    ASSERT_EQ(dynamic_cast<list<atom>*>(res)->size_of(), 2);
    ASSERT_EQ(dynamic_cast<list<atom>*>(res)->get(0)->get_value(), "a1");
    ASSERT_EQ(dynamic_cast<list<atom>*>(res)->get(1)->get_value(), "a2");
}

TEST(CarTest, should_throw_exception_when_create_car_primitive_if_passing_s_expression_is_not_a_list) {
    auto err_input = atom{"err_input"};
    ASSERT_ANY_THROW(car{&err_input});
}

TEST(CarTest, should_throw_exception_when_call_car_primitive_execute_with_empty_list) {
    auto empty_list = list<atom>{};
    auto f = car{&empty_list};
    ASSERT_ANY_THROW(f.execute());
}

TEST(CdrTest, should_get_correct_basic_info_after_successfully_init_cdr_expression) {
    auto l = list<atom>{};
    auto a1 = atom{"a1"};
    auto a2 = atom{"a2"};
    auto a3 = atom{"a3"};
    l.push_back(&a1);
    l.push_back(&a2);
    l.push_back(&a3);

    auto f = cdr{&l};
    ASSERT_EQ(f.name(), "cdr");
    ASSERT_EQ(f.return_type(), "list");
    ASSERT_EQ(f.family(), "list");
}

TEST(CdrTest, should_return_a2_a3_when_cdr_get_a1_a2_a3_list) {
    auto l = list<atom>{};
    auto a1 = atom{"a1"};
    auto a2 = atom{"a2"};
    auto a3 = atom{"a3"};
    l.push_back(&a1);
    l.push_back(&a2);
    l.push_back(&a3);

    auto f = cdr{&l};
    auto res = f.execute();

    ASSERT_EQ(res->get_indicator(), "list");
    ASSERT_EQ(reinterpret_cast<list<atom>*>(res)->size_of(), 2);
    ASSERT_EQ(reinterpret_cast<list<atom>*>(res)->get(0)->get_value(), "a2");
    ASSERT_EQ(reinterpret_cast<list<atom>*>(res)->get(1)->get_value(), "a3");
}

TEST(CdrTest, should_return_2_3_when_cdr_get_1_2_3_tuple) {
    auto l = list<integer>{};
    auto i1 = integer{1};
    auto i2 = integer{2};
    auto i3 = integer{3};
    l.push_back(&i1);
    l.push_back(&i2);
    l.push_back(&i3);

    auto f = cdr{&l};
    auto res = f.execute();

    ASSERT_EQ(res->get_indicator(), "tuple");
    ASSERT_EQ(reinterpret_cast<list<integer>*>(res)->size_of(), 2);
    ASSERT_EQ(reinterpret_cast<list<integer>*>(res)->get(0)->val(), 2);
    ASSERT_EQ(reinterpret_cast<list<integer>*>(res)->get(1)->val(), 3);
}

TEST(CdrTest, should_return_a2_a3_list_and_a4_when_cdr_get_a1_and_a2_a3_list_a4) {
    auto a1 = atom{"a1"};
    auto l1 = list<atom>{};
    auto a2 = atom{"a2"};
    auto a3 = atom{"a3"};
    l1.push_back(&a2);
    l1.push_back(&a3);

    auto l2 = list<s_expression>{};
    auto a4 = atom{"a4"};

    l2.push_back(&a1);
    l2.push_back(&l1);
    l2.push_back(&a4);

    auto f = cdr{&l2};
    auto res = f.execute();

    ASSERT_EQ(res->get_indicator(), "list");
    ASSERT_EQ(dynamic_cast<list<s_expression>*>(res)->size_of(), 2);

    s_expression* first_s_exp_in_res = dynamic_cast<list<s_expression> *>(res)->get(0);
    ASSERT_EQ(first_s_exp_in_res->get_indicator(), "list");
    ASSERT_EQ(reinterpret_cast<list<atom>*>(first_s_exp_in_res)->size_of(), 2);
    ASSERT_EQ(reinterpret_cast<list<atom>*>(first_s_exp_in_res)->get(0)->get_value(), "a2");
    ASSERT_EQ(reinterpret_cast<list<atom>*>(first_s_exp_in_res)->get(1)->get_value(), "a3");

    s_expression* second_s_exp_in_res = dynamic_cast<list<s_expression> *>(res)->get(1);
    ASSERT_EQ(second_s_exp_in_res->get_value(), "a4");
}

TEST(CdrTest, should_throw_exception_when_create_cdr_primitive_if_passing_s_expression_is_not_a_list) {
    auto err_input = atom{"err_input"};
    ASSERT_ANY_THROW(cdr{&err_input});
}

TEST(CdrTest, should_throw_exception_when_call_cdr_primitive_execute_with_empty_list) {
    auto empty_list = list<atom>{};
    auto f = cdr{&empty_list};
    ASSERT_ANY_THROW(f.execute());
}

TEST(ConsTest, should_get_correct_basic_info_after_successfully_init_cons_expression) {
    auto a1 = atom{"a1"};

    auto l = list<atom>{};
    auto a2 = atom{"a2"};
    l.push_back(&a2);

    auto f = cons{&a1, &l};
    ASSERT_EQ(f.name(), "cons");
    ASSERT_EQ(f.return_type(), "list");
    ASSERT_EQ(f.family(), "list");
}

TEST(ConsTest, should_return_a1_a2_list_when_cons_a1_to_a2_list) {
    auto a1 = atom{"a1"};

    auto l = list<atom>{};
    auto a2 = atom{"a2"};
    l.push_back(&a2);

    auto f = cons{&a1, &l};
    auto res = f.execute();
    ASSERT_EQ(res->get_indicator(), "list");

    auto res_to_list = reinterpret_cast<list<atom>*>(res);
    ASSERT_EQ(res_to_list->size_of(), 2);
    ASSERT_EQ(res_to_list->get(0)->get_value(), "a1");
    ASSERT_EQ(res_to_list->get(1)->get_value(), "a2");
}

TEST(ConsTest, should_return_1_2_tuple_when_cons_1_to_2_tuple) {
    auto i1 = integer{1};

    auto l = list<integer>{};
    auto i2 = integer{2};
    l.push_back(&i2);

    auto f = cons{&i1, &l};
    auto res = f.execute();
    ASSERT_EQ(res->get_indicator(), "tuple");

    auto res_to_list = reinterpret_cast<list<integer>*>(res);
    ASSERT_EQ(res_to_list->size_of(), 2);
    ASSERT_EQ(dynamic_cast<integer*>(res_to_list->get(0))->val(), 1);
    ASSERT_EQ(dynamic_cast<integer*>(res_to_list->get(1))->val(), 2);
}

TEST(ConsTest, should_return_a1_a2_list_in_a3_list_when_cons_a1_a2_list_to_a3_list) {
    auto l1 = list<atom>{};
    auto a1 = atom{"a1"};
    auto a2 = atom{"a2"};
    l1.push_back(&a1);
    l1.push_back(&a2);

    auto l2 = list<atom>{};
    auto a3 = atom{"a3"};
    l2.push_back(&a3);

    auto f = cons{&l1, &l2};
    auto res = f.execute();
    ASSERT_EQ(res->get_indicator(), "list");

    auto res_to_list = reinterpret_cast<list<s_expression>*>(res);
    ASSERT_EQ(res_to_list->size_of(), 2);

    auto first_element_in_res_list = reinterpret_cast<list<atom>*>(res_to_list->get(0));
    ASSERT_EQ(first_element_in_res_list->get(0)->get_value(), "a1");
    ASSERT_EQ(first_element_in_res_list->get(1)->get_value(), "a2");

    auto second_element_in_res_list = dynamic_cast<atom*>(res_to_list->get(1));
    ASSERT_EQ(second_element_in_res_list->get_value(), "a3");
}

TEST(ConsTest, should_throw_exception_when_cons_right_param_is_not_a_list) {
    auto a1 = atom{"a1"};
    auto a2 = atom{"a2"};
    ASSERT_ANY_THROW(cons(&a1, &a2));
}

TEST(IsNullTest, should_get_correct_basic_info_after_successfully_init_is_null_expression) {
    auto l = list<atom>{};
    auto f = is_null{&l};

    ASSERT_EQ(f.name(), "null?");
    ASSERT_EQ(f.return_type(), "bool");
    ASSERT_EQ(f.family(), "list");
}

TEST(IsNullTest, should_return_true_when_is_null_getting_an_empty_list) {
    auto l = list<atom>{};

    auto f = is_null{&l};
    auto res = f.execute();

    ASSERT_EQ(res->get_indicator(), "bool");
    ASSERT_TRUE(dynamic_cast<boolean*>(res)->val());
}

TEST(IsNullTest, should_return_false_when_is_null_getting_non_empty_list) {
    auto l = list<atom>{};
    auto a1 = atom{"a1"};
    l.push_back(&a1);

    auto f = is_null{&l};
    auto res = f.execute();

    ASSERT_EQ(res->get_indicator(), "bool");
    ASSERT_FALSE(dynamic_cast<boolean*>(res)->val());
}

TEST(IsNullTest, should_throw_exception_when_param_passing_to_is_null_is_not_a_list) {
    auto a1 = atom{"a1"};

    ASSERT_ANY_THROW(is_null{&a1});
}

TEST(AddTupleTest, should_get_correct_basic_info_after_successfully_init_add_tuple_expression) {
    auto l = list<integer>{};
    auto i1 = integer{1};
    l.push_back(&i1);

    auto f = add_tuple{&l};

    ASSERT_EQ(f.name(), "addtup");
    ASSERT_EQ(f.return_type(), "integer");
    ASSERT_EQ(f.family(), "list");
}

TEST(AddTupleTest, should_return_0_when_add_tuple_get_empty_tuple) {
    auto l = list<integer>{};

    auto f = add_tuple{&l};
    auto res = f.execute();

    ASSERT_EQ(res->get_indicator(), "integer");
    ASSERT_EQ(dynamic_cast<integer*>(res)->val(), 0);
}

TEST(AddTupleTest, should_return_10_when_add_tuple_get_1_2_3_4_tuple) {
    auto l = list<integer>{};
    auto i1 = integer{1};
    auto i2 = integer{2};
    auto i3 = integer{3};
    auto i4 = integer{4};
    l.push_back(&i1);
    l.push_back(&i2);
    l.push_back(&i3);
    l.push_back(&i4);

    auto f = add_tuple{&l};
    auto res = f.execute();

    ASSERT_EQ(res->get_indicator(), "integer");
    ASSERT_EQ(dynamic_cast<integer*>(res)->val(), 10);
}

TEST(AddTupleTest, should_throw_exception_when_getting_an_atom_in_add_tuple) {
    auto a1 = atom{"a1"};

    ASSERT_ANY_THROW(add_tuple{&a1});
}

TEST(AddTupleTest, should_throw_exception_when_getting_an_integer_in_add_tuple) {
    auto i1 = integer{1};

    ASSERT_ANY_THROW(add_tuple{&i1});
}

TEST(AddTupleTest, should_throw_exception_when_getting_an_atom_list_in_add_tuple) {
    auto l = list<atom>{};
    auto a1 = atom{"a1"};
    l.push_back(&a1);

    ASSERT_ANY_THROW(add_tuple{&l});
}