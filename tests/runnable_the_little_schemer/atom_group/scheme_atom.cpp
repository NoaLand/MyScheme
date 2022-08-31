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
