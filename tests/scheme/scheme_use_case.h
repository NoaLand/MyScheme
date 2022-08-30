#ifndef MYSCHEME_SCHEME_USE_CASE_H
#define MYSCHEME_SCHEME_USE_CASE_H

#include <base_test.h>

#include <utility>

#include "core/interpreter.h"

class UseCase {
public:
    UseCase(std::string i, std::string e): input(std::move(i) + "\n"), expected_output(std::move(e)) {};
    std::string input;
    std::string expected_output;
};

class SchemeUseCaseBaseTest: public BaseTest,
                             public testing::WithParamInterface<UseCase> {
protected:
    interpreter inter{context, ts};
};

#endif //MYSCHEME_SCHEME_USE_CASE_H
