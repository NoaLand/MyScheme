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

class SelfSubGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(SelfSubGroup,
                         SelfSubGroupTest,
                         testing::Values(
                                 UseCase<integer>("(sub1 5)", "4"),
                                 UseCase<integer>("(sub1 0)", "-1"),
                                 UseCase<integer>("(sub1 -1)", "should throw! sub1 is only for [0, 1, 2 ...)", true)
                         ));

TEST_P(SelfSubGroupTest, should_return_expected_self_sub_res_from_scheme_interpreter) {
    UseCase use_case = GetParam();

    scheme(use_case);
}

class IsZeroGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(IsZeroGroup,
                         IsZeroGroupTest,
                         testing::Values(
                                 UseCase<boolean>("(zero? 0)", "#t"),
                                 UseCase<boolean>("(zero? 1492)", "#f")
                         ));

TEST_P(IsZeroGroupTest, should_return_expected_is_zero_res_from_scheme_interpreter) {
    UseCase use_case = GetParam();

    scheme(use_case);
}
