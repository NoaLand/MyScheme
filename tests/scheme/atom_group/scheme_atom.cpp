#include "scheme/scheme_use_case.h"

class SchemeAtomGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(AtomGroup,
                         SchemeAtomGroupTest,
                         testing::Values(
                                 UseCase("atom", "atom: atom"),
                                 UseCase("turkey", "atom: turkey"),
                                 UseCase("u", "atom: u"),
                                 UseCase("*abc$", "atom: *abc$")
                         ));

TEST_P(SchemeAtomGroupTest, should_return_expected_atom_from_scheme_interpreter) {
    UseCase use_case = GetParam();

    scheme(use_case);
}
