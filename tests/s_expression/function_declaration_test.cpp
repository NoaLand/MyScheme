#include "base_test.h"

#include "s_expression/atom.h"


class FunctionDeclarationAndContextTest : public BaseTest {
protected:
    std::shared_ptr<function_declaration> my_lambda{};
    const std::string my_lambda_body = "(car $l$ )";

    void SetUp() override {
        auto my_lambda_params = new list<param>();
        my_lambda_params->push_back(new param{"l"});
        my_lambda = std::make_shared<function_declaration>(
                "my_lambda",
                my_lambda_params,
                my_lambda_body
        );
        context.store(my_lambda.get());
    }
};

TEST_F(FunctionDeclarationAndContextTest, should_get_info_of_lat_function_successfully_after_init_function) {
    std::string function_definition_body = "-> name: my_lambda\n-> var: ( l )\n-> body: (car $l$ )";

    ASSERT_EQ(my_lambda->get_indicator(), "customized_function");
    ASSERT_EQ(my_lambda->get_name(), "my_lambda");
    ASSERT_EQ(my_lambda->get_params()->size_of(), 1);
    ASSERT_EQ(my_lambda->get_params()->get(0)->get_value(), "l");
    ASSERT_EQ(my_lambda->get_value(), function_definition_body);

    std::ostringstream buf;
    my_lambda->print(buf);
    ASSERT_EQ(buf.str(), "---- func ----\n" + function_definition_body + "\n");
}

TEST_F(FunctionDeclarationAndContextTest, should_return_true_when_function_has_been_stored_in_context) {
    ASSERT_TRUE(context.is_in("my_lambda"));
}

TEST_F(FunctionDeclarationAndContextTest, should_return_false_when_function_is_not_in_context) {
    ASSERT_FALSE(context.is_in("leftmost"));
}

TEST_F(FunctionDeclarationAndContextTest, should_throw_exception_when_store_function_already_exist) {
    ASSERT_ANY_THROW(context.store(my_lambda.get()));
}