#ifndef MYSCHEME_BASE_TEST_H
#define MYSCHEME_BASE_TEST_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "core/function_context.h"
#include "token/token_stream.h"
#include "s_expression/function_declaration.h"

using ::testing::HasSubstr;

class BaseTest: public testing::Test {
protected:
    std::istringstream is;
    std::ostringstream os;
    function_context context;
    Token_stream ts{is, os, &context};
};

#endif //MYSCHEME_BASE_TEST_H
