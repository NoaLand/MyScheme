#include <gtest/gtest.h>

#include "core/interpreter.h"

class InterpreterTest: public testing::Test {
protected:
    std::istringstream is;
    function_context context;
    Token_stream ts{is, &context};
};