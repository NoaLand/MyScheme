#include <gtest/gtest.h>

#include "s_expression/list.h"
#include "function/others.h"
#include "function/list_family.h"

TEST(QuoteTest, should_get_correct_basic_info_when_successfully_create_quote_expression) {
    auto a = new atom{"a"};
    auto f = new quote{a};

    ASSERT_EQ(f->name(), "quote");
    ASSERT_EQ(f->return_type(), "atom");
    ASSERT_EQ(f->family(), "other");
}

TEST(QuoteTest, should_return_a_when_quote_atom_a) {
    auto a = new atom{"a"};

    auto f = new quote{a};
    auto res = f->execute();

    ASSERT_EQ(res->get_indicator(), "atom");
    ASSERT_EQ(res->get_value(), "a");
}

TEST(QuoteTest, should_return_a1_when_quote_car_a1_a2_a3_list) {
    auto l = new list<atom>{};
    auto a1 = new atom{"a1"};
    auto a2 = new atom{"a2"};
    auto a3 = new atom{"a3"};
    l->push_back(a1);
    l->push_back(a2);
    l->push_back(a3);

    auto c = new car{l};
    auto car_res = c->execute();

    auto f = new quote{car_res};
    auto res = f->execute();

    ASSERT_EQ(res->get_indicator(), "atom");
    ASSERT_EQ(res->get_value(), "a1");
}