#include <gtest/gtest.h>

#include "s_expression/atom.h"

TEST(AtomTest, should_get_value_successfully_after_create_atom) {
    auto a = new atom{"value_of_atom"};
    const std::string& atom_value = a->get_value();
    const std::string& atom_indicator = a->get_indicator();
    ASSERT_EQ(atom_value, "value_of_atom");
    ASSERT_EQ(atom_indicator, "atom");
}