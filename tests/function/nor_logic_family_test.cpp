#include <gtest/gtest.h>

#include "function/nor_logic_family.h"

TEST(OrLogicTest, should_get_correct_basic_info_when_successfully_create_or_logic_expression) {
    auto l = std::make_shared<boolean>(true);
    auto r = std::make_shared<boolean>(false);

    auto f = or_logic{l, r};

    ASSERT_EQ(f.name(), "or?");
    ASSERT_EQ(f.return_type(), "bool");
    ASSERT_EQ(f.family(), "nor_logic");
}

TEST(OrLogicTest, should_return_true_when_r_or_l_is_true) {
    auto l = std::make_shared<boolean>(true);
    auto r = std::make_shared<boolean>(false);

    auto f = or_logic{l, r};
    auto res = f.execute();

    ASSERT_EQ(res->get_indicator(), "bool");
    ASSERT_TRUE(dynamic_pointer_cast<boolean>(res)->val());
}

TEST(OrLogicTest, should_return_true_when_r_and_l_are_true) {
    auto l = std::make_shared<boolean>(true);
    auto r = std::make_shared<boolean>(true);

    auto f = or_logic{l, r};
    auto res = f.execute();

    ASSERT_EQ(res->get_indicator(), "bool");
    ASSERT_TRUE(dynamic_pointer_cast<boolean>(res)->val());
}

TEST(OrLogicTest, should_return_false_when_r_and_l_are_false) {
    auto l = std::make_shared<boolean>(false);
    auto r = std::make_shared<boolean>(false);

    auto f = or_logic{l, r};
    auto res = f.execute();

    ASSERT_EQ(res->get_indicator(), "bool");
    ASSERT_FALSE(dynamic_pointer_cast<boolean>(res)->val());
}

TEST(OrLogicTest, should_throw_exception_when_l_is_not_a_boolean_type) {
    auto l = std::make_shared<atom>("rong_input_type");
    auto r = std::make_shared<boolean>(true);

    ASSERT_ANY_THROW(or_logic(l, r));
}

TEST(OrLogicTest, should_throw_exception_when_r_is_not_a_boolean_type) {
    auto l = std::make_shared<boolean>(true);
    auto r = std::make_shared<atom>("wrong_input_type");

    ASSERT_ANY_THROW(or_logic(l, r));
}

TEST(AndLogicTest, should_get_correct_basic_info_when_successfully_create_and_logic_expression) {
    auto l = std::make_shared<boolean>(true);
    auto r = std::make_shared<boolean>(false);

    auto f = and_logic{l, r};

    ASSERT_EQ(f.name(), "and?");
    ASSERT_EQ(f.return_type(), "bool");
    ASSERT_EQ(f.family(), "nor_logic");
}

TEST(AndLogicTest, should_return_true_when_r_and_l_are_true) {
    auto l = std::make_shared<boolean>(true);
    auto r = std::make_shared<boolean>(true);

    auto f = or_logic{l, r};
    auto res = f.execute();

    ASSERT_EQ(res->get_indicator(), "bool");
    ASSERT_TRUE(dynamic_pointer_cast<boolean>(res)->val());
}

TEST(AndLogicTest, should_return_false_when_r_is_false) {
    auto l = std::make_shared<boolean>(true);
    auto r = std::make_shared<boolean>(false);

    auto f = and_logic{l, r};
    auto res = f.execute();

    ASSERT_EQ(res->get_indicator(), "bool");
    ASSERT_FALSE(dynamic_pointer_cast<boolean>(res)->val());
}

TEST(AndLogicTest, should_return_false_when_r_and_l_are_false) {
    auto l = std::make_shared<boolean>(false);
    auto r = std::make_shared<boolean>(false);

    auto f = and_logic{l, r};
    auto res = f.execute();

    ASSERT_EQ(res->get_indicator(), "bool");
    ASSERT_FALSE(dynamic_pointer_cast<boolean>(res)->val());
}

TEST(AndLogicTest, should_throw_exception_when_l_is_not_a_boolean_type) {
    auto l = std::make_shared<atom>("wrong_input_type");
    auto r = std::make_shared<boolean>(true);

    ASSERT_ANY_THROW(and_logic(l, r));
}

TEST(AndLogicTest, should_throw_exception_when_r_is_not_a_boolean_type) {
    auto l = std::make_shared<boolean>(true);
    auto r = std::make_shared<atom>("wrong_input_type");

    ASSERT_ANY_THROW(and_logic(l, r));
}
