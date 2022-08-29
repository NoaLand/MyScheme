#include <gtest/gtest.h>

#include "s_expression/list.h"
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

TEST(IsAtomTest, should_return_true_when_input_is_a_boolean) {
    auto b = new boolean{true};

    auto f = new is_atom{b};
    auto res = f->execute();

    ASSERT_EQ(res->get_indicator(), "bool");
    ASSERT_TRUE(res->val());
}

TEST(IsAtomTest, should_return_true_when_input_is_an_integer) {
    auto i = new integer{1};

    auto f = new is_atom{i};
    auto res = f->execute();

    ASSERT_EQ(res->get_indicator(), "bool");
    ASSERT_TRUE(res->val());
}

TEST(IsAtomTest, should_return_false_when_input_is_a_list) {
    auto l = new list<atom>{};

    auto f = new is_atom{l};
    auto res = f->execute();

    ASSERT_EQ(res->get_indicator(), "bool");
    ASSERT_FALSE(res->val());
}

TEST(IsNumberTest, should_get_basic_info_when_successfully_create_is_number_expression) {
    auto a = new atom{"a"};
    auto f = new is_number{a};

    ASSERT_EQ(f->name(), "number?");
    ASSERT_EQ(f->return_type(), "bool");
    ASSERT_EQ(f->family(), "s_expression");
}

TEST(IsNumberTest, should_return_true_when_input_is_a_number) {
    auto i = new integer{1};

    auto f = new is_number{i};
    auto res = f->execute();

    ASSERT_EQ(res->get_indicator(), "bool");
    ASSERT_TRUE(res->val());
}


TEST(IsNumberTest, should_return_false_when_input_is_an_atom) {
    auto a = new atom{"a"};

    auto f = new is_number{a};
    auto res = f->execute();

    ASSERT_EQ(res->get_indicator(), "bool");
    ASSERT_FALSE(res->val());
}

TEST(IsNumberTest, should_return_false_when_input_is_a_list) {
    auto l = new list<atom>{};

    auto f = new is_number{l};
    auto res = f->execute();

    ASSERT_EQ(res->get_indicator(), "bool");
    ASSERT_FALSE(res->val());
}

TEST(IsEqTest, should_get_basic_info_when_successfully_create_is_eq_expression) {
    auto l = new atom{"l"};
    auto r = new atom{"r"};
    auto f = new is_eq{l, r};

    ASSERT_EQ(f->name(), "eq?");
    ASSERT_EQ(f->return_type(), "bool");
    ASSERT_EQ(f->family(), "s_expression");
}

TEST(IsEqTest, should_return_true_when_l_and_r_are_same_in_type_and_value) {
    auto l = new atom{"a1"};
    auto r = new atom{"a1"};

    auto f = new is_eq{l, r};
    auto res = f->execute();

    ASSERT_EQ(res->get_indicator(), "bool");
    ASSERT_TRUE(res->val());
}

TEST(IsEqTest, should_return_false_when_l_is_atom_and_r_is_list_of_l) {
    auto l = new atom{"a"};

    auto r = new list<atom>{};
    r->push_back(l);

    auto f = new is_eq{l, r};
    auto res = f->execute();

    ASSERT_EQ(res->get_indicator(), "bool");
    ASSERT_FALSE(res->val());
}

TEST(IsEqTest, should_return_false_when_l_is_atom_and_r_is_bool) {
    auto l = new atom{"a"};
    auto r = new boolean{true};

    auto f = new is_eq{l, r};
    auto res = f->execute();

    ASSERT_EQ(res->get_indicator(), "bool");
    ASSERT_FALSE(res->val());
}