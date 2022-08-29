#include <gtest/gtest.h>

#include "function/others.h"

TEST(QuoteTest, should_get_correct_basic_info_when_successfully_create_quote_expression) {
    auto a = new atom{"a"};
    auto f = new quote{a};

    ASSERT_EQ(f->name(), "quote");
    ASSERT_EQ(f->return_type(), "atom");
    ASSERT_EQ(f->family(), "other");
}