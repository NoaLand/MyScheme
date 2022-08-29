#ifndef MYSCHEME_BASE_TEST_H
#define MYSCHEME_BASE_TEST_H

#include <gtest/gtest.h>
#include "s_expression/function_declaration.h"
#include "token/token.h"

class BaseTest: public testing::Test {
protected:
    std::istringstream is;
    function_context context;
    Token_stream ts{is, &context};
};

#endif //MYSCHEME_BASE_TEST_H
