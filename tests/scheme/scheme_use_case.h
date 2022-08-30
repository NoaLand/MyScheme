#ifndef MYSCHEME_SCHEME_USE_CASE_H
#define MYSCHEME_SCHEME_USE_CASE_H

#include <base_test.h>

#include "core/interpreter.h"

class SchemeUseCaseBaseTest: public BaseTest,
                             public testing::WithParamInterface<std::string> {
protected:
    interpreter inter{context, ts};
};

#endif //MYSCHEME_SCHEME_USE_CASE_H
