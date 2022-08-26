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

TEST(FunctionContextTest, should_return_true_when_function_has_been_stored_in_context) {
    function_context context;

    auto lat_params = new list<param>();
    lat_params->push_back(new param{"l"});
    std::string lat_body = "(cond ( ( null? $l$ ) #t ) ( ( atom? ( car $l$ ) ) ( lat? ( cdr $l$ ) ) ) ( else #f ) )";
    auto lat = new function_declaration(
            "lat?",
            lat_params,
            lat_body
    );

    context.store(lat);

    ASSERT_EQ(context.is_in("lat?"), true);
}

TEST(FunctionContextTest, should_return_false_when_function_is_not_in_context) {
    function_context context;

    ASSERT_EQ(context.is_in("lat?"), false);
}

TEST(FunctionContextTest, should_throw_exception_when_store_function_already_exist) {
    function_context context;

    auto lat_params = new list<param>();
    lat_params->push_back(new param{"l"});
    std::string lat_body = "(cond ( ( null? $l$ ) #t ) ( ( atom? ( car $l$ ) ) ( lat? ( cdr $l$ ) ) ) ( else #f ) )";
    auto lat = new function_declaration(
            "lat?",
            lat_params,
            lat_body
    );

    context.store(lat);

    ASSERT_ANY_THROW(context.store(lat));
}