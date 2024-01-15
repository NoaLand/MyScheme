#include <gtest/gtest.h>

#include "s_expression/atom.h"
#include "s_expression/list.h"

TEST(ListTest, should_return_tuple_when_list_is_empty) {
    auto l = std::make_shared<list<atom>>();

    ASSERT_EQ(l->get_indicator(), "tuple");
}

TEST(ListTest, should_return_3_when_list_has_3_value) {
    auto a1 = std::make_shared<atom>("a1");
    auto a2 = std::make_shared<atom>("a2");
    auto a3 = std::make_shared<atom>("a3");
    auto l = std::make_shared<list<atom>>();

    l->push_back(a1);
    l->push_back(a2);
    l->push_back(a3);

    ASSERT_EQ(l->size_of(), 3);
}

TEST(ListTest, should_successfully_push_2_different_type_value_in_s_expression_list) {
    auto a1 = std::make_shared<atom>("a1");
    auto b2 = std::make_shared<boolean>(true);
    auto l = std::make_shared<list<s_expression>>();

    l->push_back(a1);
    l->push_back(b2);

    ASSERT_EQ(l->size_of(), 2);
}

TEST(ListTest, should_return_true_when_list_is_empty) {
    auto l = std::make_shared<list<s_expression>>();

    ASSERT_TRUE(l->empty());

    std::ostringstream buf;
    l->print(buf);
    ASSERT_EQ(buf.str(), "tuple: ( )\n");
}

TEST(ListTest, should_return_false_when_list_has_value) {
    auto a1 = std::make_shared<atom>("a1");
    auto l = std::make_shared<list<atom>>();

    l->push_back(a1);

    ASSERT_FALSE(l->empty());
}

TEST(ListTest, should_contain_a1_when_already_push_into_it) {
    auto a1 = std::make_shared<atom>("a1");
    auto l = std::make_shared<list<atom>>();

    l->push_back(a1);

    ASSERT_TRUE(l->has_value("a1"));
}

TEST(ListTest, should_return_not_contain_when_a1_is_not_in_list) {
    auto l = std::make_shared<list<atom>>();

    ASSERT_FALSE(l->has_value("a1"));
}

TEST(ListTest, should_return_value_of_list_successfully_after_input_atoms) {
    auto a1 = std::make_shared<atom>("a1");
    auto a2 = std::make_shared<atom>("a2");
    auto a3 = std::make_shared<atom>("a3");
    auto l = std::make_shared<list<atom>>();

    l->push_back(a1);
    l->push_back(a2);
    l->push_back(a3);

    ASSERT_EQ(l->get_value(), "( a1 a2 a3 )");
    ASSERT_EQ(l->get_indicator(), "list");

    std::ostringstream buf;
    l->print(buf);
    ASSERT_EQ(buf.str(), "list: ( a1 a2 a3 )\n");
}

TEST(ListTest, should_return_iterator_successfully_when_get_iterator) {
    auto a1 = std::make_shared<atom>("a1");
    auto a2 = std::make_shared<atom>("a2");
    auto a3 = std::make_shared<atom>("a3");
    auto l = std::make_shared<list<atom>>();

    l->push_back(a1);
    l->push_back(a2);
    l->push_back(a3);

    ASSERT_EQ(l->get_iterator().size(), 3);
}