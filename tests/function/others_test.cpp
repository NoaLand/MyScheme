#include <gtest/gtest.h>

#include "s_expression/list.h"
#include "function/others.h"
#include "function/list_family.h"

TEST(QuoteTest, should_get_correct_basic_info_when_successfully_create_quote_expression) {
    auto a = std::make_shared<atom>("a");
    auto f = quote{a};

    ASSERT_EQ(f.name(), "quote");
    ASSERT_EQ(f.return_type(), "atom");
    ASSERT_EQ(f.family(), "other");
}

TEST(QuoteTest, should_return_a_when_quote_atom_a) {
    auto a = std::make_shared<atom>("a");

    auto f = quote{a};
    auto res = f.execute();

    ASSERT_EQ(res->get_indicator(), "atom");
    ASSERT_EQ(res->get_value(), "a");
}

TEST(QuoteTest, should_return_a1_when_quote_car_a1_a2_a3_list) {
    auto l = std::make_shared<list<atom>>();
    auto a1 = std::make_shared<atom>("a1");
    auto a2 = std::make_shared<atom>("a2");
    auto a3 = std::make_shared<atom>("a3");
    l->push_back(a1);
    l->push_back(a2);
    l->push_back(a3);

    auto c = car{l};
    auto car_res = c.execute();

    auto f = quote{car_res};
    auto res = f.execute();

    ASSERT_EQ(res->get_indicator(), "atom");
    ASSERT_EQ(res->get_value(), "a1");
}

TEST(QuoteTest, should_return_a1_a2_a3_list_value_when_quote_a1_a2_a3_list) {
    auto l = std::make_shared<list<atom>>();
    auto a1 = std::make_shared<atom>("a1");
    auto a2 = std::make_shared<atom>("a2");
    auto a3 = std::make_shared<atom>("a3");
    l->push_back(a1);
    l->push_back(a2);
    l->push_back(a3);

    auto f = quote{l};
    auto res = f.execute();

    ASSERT_EQ(res->get_indicator(), "atom");
    ASSERT_EQ(res->get_value(), "( a1 a2 a3 )");
}

TEST(QuoteTest, should_return_t_atom_when_quote_true_boolean) {
    auto b = std::make_shared<boolean>(true);

    auto f = quote{b};
    auto res = f.execute();

    ASSERT_EQ(res->get_indicator(), "atom");
    ASSERT_EQ(res->get_value(), "#t");
}

TEST(QuoteTest, should_return_f_atom_when_quote_false_boolean) {
    auto b = std::make_shared<boolean>(false);

    auto f = quote{b};
    auto res = f.execute();

    ASSERT_EQ(res->get_indicator(), "atom");
    ASSERT_EQ(res->get_value(), "#f");
}
