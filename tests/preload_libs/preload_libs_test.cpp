#include <gtest/gtest.h>

#include "preload_libs/preload_libs.h"

TEST(DISABLED_PreloadLibsTest, should_contain_loaded_func_when_searching_for_lat) {
    auto context = function_context{};
    preload_libs(context);

    ASSERT_TRUE(context.is_in("lat?"));
    ASSERT_TRUE(context.is_in("length"));
    ASSERT_TRUE(context.is_in("member?"));
    ASSERT_TRUE(context.is_in("rember"));
    ASSERT_TRUE(context.is_in("pick"));
    ASSERT_TRUE(context.is_in("rempick"));
    ASSERT_TRUE(context.is_in("+"));
    ASSERT_TRUE(context.is_in("-"));
    ASSERT_TRUE(context.is_in("*"));
    ASSERT_TRUE(context.is_in("/"));
    ASSERT_TRUE(context.is_in(">"));
    ASSERT_TRUE(context.is_in("<"));
    ASSERT_TRUE(context.is_in("="));
    ASSERT_TRUE(context.is_in("^"));
}
