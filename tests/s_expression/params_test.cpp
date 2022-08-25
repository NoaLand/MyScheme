#include <gtest/gtest.h>

#include "s_expression/params.h"

TEST(ParamsTest, should_get_value_successfully_after_create_param) {
    auto p = new param{"value_of_param"};
    const std::string& param_to_string = p->get_value();
    const std::string& param_indicator = p->get_indicator();

    ASSERT_EQ(param_to_string, "value_of_param");
    ASSERT_EQ(param_indicator, "param");
}
