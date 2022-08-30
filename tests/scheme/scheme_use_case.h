#ifndef MYSCHEME_SCHEME_USE_CASE_H
#define MYSCHEME_SCHEME_USE_CASE_H

#include <base_test.h>

#include <utility>

#include "core/interpreter.h"

class UseCase {
public:
    UseCase(std::string i, std::string e, bool exception = false): input(std::move(i) + "\n"), expected_output(std::move(e)), handle_throw(exception) {};
    std::string input;
    std::string expected_output;
    bool handle_throw;
};

class SchemeUseCaseBaseTest: public BaseTest,
                             public testing::WithParamInterface<UseCase> {
protected:
    interpreter inter{context, ts};

    inline void scheme(UseCase& use_case) {
        std::string expression = use_case.input;
        is.str(expression);

        if(use_case.handle_throw) {
            ASSERT_ANY_THROW(inter.scheme());
            std::cout << use_case.expected_output << std::endl;
        } else {
            inter.scheme();
            ASSERT_THAT(os.str(), HasSubstr(use_case.expected_output));
        }
    }
};

#endif //MYSCHEME_SCHEME_USE_CASE_H
