#include <gtest/gtest.h>

#include "s_expression/function_declaration.h"


class FunctionDeclarationAndContextTest : public ::testing::Test {
protected:
    void SetUp() override {
        auto lat_params = new list<param>();
        lat_params->push_back(new param{"l"});
        lat = std::make_shared<function_declaration>(
                "lat?",
                lat_params,
                lat_body
        );
    }

    std::shared_ptr<function_declaration> lat{};
    const std::string lat_body = "(cond ( ( null? $l$ ) #t ) ( ( atom? ( car $l$ ) ) ( lat? ( cdr $l$ ) ) ) ( else #f ) )";
};

TEST_F(FunctionDeclarationAndContextTest, should_get_info_of_lat_function_successfully_after_init_function) {
    std::string function_definition_body = "-> name: lat?\n-> var: ( l )\n-> body: (cond ( ( null? $l$ ) #t ) ( ( atom? ( car $l$ ) ) ( lat? ( cdr $l$ ) ) ) ( else #f ) )";

    ASSERT_EQ(lat->get_indicator(), "customized_function");
    ASSERT_EQ(lat->get_name(), "lat?");
    ASSERT_EQ(lat->get_params()->size_of(), 1);
    ASSERT_EQ(lat->get_params()->get(0)->get_value(), "l");
    ASSERT_EQ(lat->get_body(), lat_body);
    ASSERT_EQ(lat->get_value(), function_definition_body);

    std::ostringstream buf;
    lat->print(buf);
    ASSERT_EQ(buf.str(), "---- func ----\n" + function_definition_body + "\n");
}

TEST_F(FunctionDeclarationAndContextTest, should_return_true_when_function_has_been_stored_in_context) {
    function_context context;
    context.store(lat.get());

    ASSERT_EQ(context.is_in("lat?"), true);
}

TEST_F(FunctionDeclarationAndContextTest, should_return_false_when_function_is_not_in_context) {
    function_context context;

    ASSERT_EQ(context.is_in("lat?"), false);
}

TEST_F(FunctionDeclarationAndContextTest, should_throw_exception_when_store_function_already_exist) {
    function_context context;
    context.store(lat.get());

    ASSERT_ANY_THROW(context.store(lat.get()));
}