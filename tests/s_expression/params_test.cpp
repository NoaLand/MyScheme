#include <gtest/gtest.h>

#include "s_expression/params.h"

TEST(ParamsTest, should_get_value_successfully_after_create_param) {
    auto p = param{"value_of_param"};
    ASSERT_EQ(p.get_value(), "value_of_param");
    ASSERT_EQ(p.get_indicator(), "param");

    std::ostringstream buf;
    p.print(buf);
    ASSERT_EQ(buf.str(), "param: value_of_param\n");
}
