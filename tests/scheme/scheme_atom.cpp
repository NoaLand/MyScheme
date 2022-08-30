#include <base_test.h>

#include "core/interpreter.h"

class SchemeAtomGroupTest: public BaseTest,
                           public testing::WithParamInterface<std::string> {
protected:
    interpreter inter{context, ts};
};

INSTANTIATE_TEST_SUITE_P(AtomGroup,
                         SchemeAtomGroupTest,
                         testing::Values("atom", "turkey", "u", "*abc$"));

TEST_P(SchemeAtomGroupTest, should_return_F_type_when_token_is_stored) {
    std::string an_atom = GetParam() + "\n";
    is.str(an_atom);

    inter.scheme();

    ASSERT_THAT(os.str(), HasSubstr("atom: " + an_atom));
}
