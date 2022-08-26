#include <gtest/gtest.h>

#include "s_expression/function_declaration.h"
#include "s_expression/atom.h"


class FunctionDeclarationAndContextTest : public ::testing::Test {
protected:
    function_context context;
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
    ASSERT_EQ(my_lambda->get_body(), my_lambda_body);
    ASSERT_EQ(my_lambda->get_value(), function_definition_body);

    std::ostringstream buf;
    my_lambda->print(buf);
    ASSERT_EQ(buf.str(), "---- func ----\n" + function_definition_body + "\n");
}

TEST_F(FunctionDeclarationAndContextTest, should_return_true_when_function_has_been_stored_in_context) {
    ASSERT_EQ(context.is_in("my_lambda"), true);
}

TEST_F(FunctionDeclarationAndContextTest, should_return_false_when_function_is_not_in_context) {
    ASSERT_EQ(context.is_in("leftmost"), false);
}

TEST_F(FunctionDeclarationAndContextTest, should_throw_exception_when_store_function_already_exist) {
    ASSERT_ANY_THROW(context.store(my_lambda.get()));
}

TEST_F(FunctionDeclarationAndContextTest, should_instantiate_success_when_passing_valid_params) {
    auto input = new list<atom>;
    input->push_back(new atom{"a"});
    input->push_back(new atom{"b"});
    input->push_back(new atom{"c"});

    auto input_params = new list<s_expression>{};
    input_params->push_back(input);
    
    context.is_in("my_lambda", true);
    const std::string& evaluated_body = context.instantiate(input_params);

    ASSERT_EQ(evaluated_body, "(car ( a b c ) )");
}

TEST_F(FunctionDeclarationAndContextTest, should_throw_exception_when_input_num_is_not_match) {
    auto err_input_1 = new atom{"err_input_1"};
    auto err_input_2 = new atom{"err_input_2"};

    auto wrong_input_params_num = new list<s_expression>{};
    wrong_input_params_num->push_back(err_input_1);
    wrong_input_params_num->push_back(err_input_2);

    context.is_in("my_lambda", true);

    ASSERT_ANY_THROW(context.instantiate(wrong_input_params_num));
}