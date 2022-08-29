#include <gtest/gtest.h>

#include "function/others.h"

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