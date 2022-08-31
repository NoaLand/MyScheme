#include "runnable_the_little_schemer//scheme_use_case.h"

class SchemeAtomGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(AtomGroup,
                         SchemeAtomGroupTest,
                         testing::Values(
                                 UseCase<atom>("atom", "atom"),
                                 UseCase<atom>("turkey", "turkey"),
                                 UseCase<atom>("u", "u"),
                                 UseCase<atom>("*abc$", "*abc$")
                         ));

TEST_P(SchemeAtomGroupTest, should_return_expected_atom_from_scheme_interpreter) {
    UseCase<s_expression> use_case = GetParam();

    scheme(use_case);
}

class IntegerGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(IntegerGroup,
                         IntegerGroupTest,
                         testing::Values(
                                 UseCase<integer>("1", "1"),
                                 UseCase<integer>("3", "3"),
                                 UseCase<integer>("5", "5"),
                                 UseCase<integer>("7", "7")
                         ));

TEST_P(IntegerGroupTest, should_return_expected_integer_from_scheme_interpreter) {
    UseCase<s_expression> use_case = GetParam();

    scheme(use_case);
}

class BooleanGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(BooleanGroup,
                         BooleanGroupTest,
                         testing::Values(
                                 UseCase<boolean>("#t", "#t"),
                                 UseCase<boolean>("else", "#t"),
                                 UseCase<boolean>("#f", "#f")
                         ));

TEST_P(BooleanGroupTest, should_return_expected_boolean_from_scheme_interpreter) {
    UseCase<s_expression> use_case = GetParam();

    scheme(use_case);
}
