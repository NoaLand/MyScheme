#include <gtest/gtest.h>

#include "s_expression/atom.h"
#include "s_expression/list.h"

TEST(ListTest, should_return_tuple_when_list_is_empty) {
    auto l = new list<atom>{};

    ASSERT_EQ(l->get_indicator(), "tuple");
}

TEST(ListTest, should_return_3_when_list_has_3_value) {
    auto a1 = new atom{"a1"};
    auto a2 = new atom{"a2"};
    auto a3 = new atom{"a3"};
    auto l = new list<atom>{};

    l->push_back(a1);
    l->push_back(a2);
    l->push_back(a3);

    ASSERT_EQ(l->size_of(), 3);
}

TEST(ListTest, should_return_true_when_list_is_empty) {
    auto l = new list<s_expression>{};

    ASSERT_EQ(l->empty(), true);
}

TEST(ListTest, should_return_false_when_list_has_value) {
    auto a1 = new atom{"a1"};
    auto l = new list<atom>{};

    l->push_back(a1);

    ASSERT_EQ(l->empty(), false);
}

TEST(ListTest, should_contain_a1_when_already_push_into_it) {
    auto a1 = new atom{"a1"};
    auto l = new list<atom>{};

    l->push_back(a1);

    ASSERT_EQ(l->has_value("a1"), true);
}

TEST(ListTest, should_return_value_of_list_successfully_after_input_atoms) {
    auto a1 = new atom{"a1"};
    auto a2 = new atom{"a2"};
    auto a3 = new atom{"a3"};
    auto l = new list<atom>{};

    l->push_back(a1);
    l->push_back(a2);
    l->push_back(a3);

    ASSERT_EQ(l->get_value(), "( a1 a2 a3 )");
    ASSERT_EQ(l->get_indicator(), "list");
}