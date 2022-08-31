#include "runnable_the_little_schemer/scheme_use_case.h"

class SelfAddGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(SelfAddGroup,
                         SelfAddGroupTest,
                         testing::Values(
                                 UseCase<integer>("(add1 67)", "68"),
                                 UseCase<integer>("(add1 x)", "should throw! add1 is only for integer", true)
                         ));

TEST_P(SelfAddGroupTest, should_return_expected_self_add_res_from_scheme_interpreter) {
    UseCase use_case = GetParam();

    scheme(use_case);
}
