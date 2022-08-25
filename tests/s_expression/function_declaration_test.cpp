#include <gtest/gtest.h>

#include "s_expression/function_declaration.h"

TEST(FunctionDeclarationTest, should_get_info_of_lat_function_successfully_after_init_function) {
    auto lat_params = new list<param>();
    lat_params->push_back(new param{"l"});
    std::string lat_body = "(cond ( ( null? $l$ ) #t ) ( ( atom? ( car $l$ ) ) ( lat? ( cdr $l$ ) ) ) ( else #f ) )";
    auto lat = new function_declaration(
            "lat?",
            lat_params,
            lat_body
    );

    ASSERT_EQ(lat->get_indicator(), "customized_function");
    ASSERT_EQ(lat->get_name(), "lat?");
    ASSERT_EQ(lat->get_params()->size_of(), 1);
    ASSERT_EQ(lat->get_params()->get(0)->get_value(), "l");
    ASSERT_EQ(lat->get_body(), lat_body);
}