#include <gtest/gtest.h>

#include "s_expression/list.h"
#include "function/s_expression_family.h"
#include "function/others.h"

TEST(IsAtomTest, should_get_basic_info_when_successfully_create_is_atom_expression) {
    auto a = atom{"a"};
    auto f = is_atom{&a};

    ASSERT_EQ(f.name(), "atom?");
    ASSERT_EQ(f.return_type(), "bool");
    ASSERT_EQ(f.family(), "s_expression");
}

TEST(IsAtomTest, should_return_true_when_input_is_an_atom) {
    auto a = atom{"a"};

    auto f = is_atom{&a};
    auto res = f.execute();

    ASSERT_EQ(res->get_indicator(), "bool");
    ASSERT_TRUE(res->val());
}

TEST(IsAtomTest, should_return_true_when_input_is_a_boolean) {
    auto b = boolean{true};

    auto f = is_atom{&b};
    auto res = f.execute();

    ASSERT_EQ(res->get_indicator(), "bool");
    ASSERT_TRUE(res->val());
}

TEST(IsAtomTest, should_return_true_when_input_is_an_integer) {
    auto i = integer{1};

    auto f = is_atom{&i};
    auto res = f.execute();

    ASSERT_EQ(res->get_indicator(), "bool");
    ASSERT_TRUE(res->val());
}

TEST(IsAtomTest, should_return_false_when_input_is_a_list) {
    auto l = list<atom>{};

    auto f = is_atom{&l};
    auto res = f.execute();

    ASSERT_EQ(res->get_indicator(), "bool");
    ASSERT_FALSE(res->val());
}

TEST(IsNumberTest, should_get_basic_info_when_successfully_create_is_number_expression) {
    auto a = atom{"a"};
    auto f = is_number{&a};

    ASSERT_EQ(f.name(), "number?");
    ASSERT_EQ(f.return_type(), "bool");
    ASSERT_EQ(f.family(), "s_expression");
}

TEST(IsNumberTest, should_return_true_when_input_is_a_number) {
    auto i = integer{1};

    auto f = is_number{&i};
    auto res = f.execute();

    ASSERT_EQ(res->get_indicator(), "bool");
    ASSERT_TRUE(res->val());
}

TEST(IsNumberTest, should_return_false_when_input_is_an_atom) {
    auto a = atom{"a"};

    auto f = is_number{&a};
    auto res = f.execute();

    ASSERT_EQ(res->get_indicator(), "bool");
    ASSERT_FALSE(res->val());
}

TEST(IsNumberTest, should_return_false_when_input_is_a_list) {
    auto l = list<atom>{};

    auto f = is_number{&l};
    auto res = f.execute();

    ASSERT_EQ(res->get_indicator(), "bool");
    ASSERT_FALSE(res->val());
}

TEST(IsEqTest, should_get_basic_info_when_successfully_create_is_eq_expression) {
    auto l = atom{"l"};
    auto r = atom{"r"};
    auto f = is_eq{&l, &r};

    ASSERT_EQ(f.name(), "eq?");
    ASSERT_EQ(f.return_type(), "bool");
    ASSERT_EQ(f.family(), "s_expression");
}

TEST(IsEqTest, should_return_true_when_l_and_r_are_same_in_type_and_value) {
    auto l = atom{"a1"};
    auto r = atom{"a1"};

    auto f = is_eq{&l, &r};
    auto res = f.execute();

    ASSERT_EQ(res->get_indicator(), "bool");
    ASSERT_TRUE(res->val());
}

TEST(IsEqTest, should_return_false_when_l_is_atom_and_r_is_list_of_l) {
    auto l = atom{"a"};

    auto r = list<atom>{};
    r.push_back(&l);

    auto f = is_eq{&l, &r};
    auto res = f.execute();

    ASSERT_EQ(res->get_indicator(), "bool");
    ASSERT_FALSE(res->val());
}

TEST(IsEqTest, should_return_false_when_l_is_atom_and_r_is_bool) {
    auto l = atom{"a"};
    auto r = boolean{true};

    auto f = is_eq{&l, &r};
    auto res = f.execute();

    ASSERT_EQ(res->get_indicator(), "bool");
    ASSERT_FALSE(res->val());
}

TEST(IsEqTest, should_return_false_when_l_is_true_and_r_is_quote_true) {
    auto l = boolean{true};

    auto quote_func = quote{&l};
    auto r = quote_func.execute();

    auto f = is_eq{&l, r};
    auto res = f.execute();

    ASSERT_EQ(res->get_indicator(), "bool");
    ASSERT_FALSE(res->val());
}