#include "scheme/scheme_use_case.h"

class IsAtomGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(IsAtomGroup,
                         IsAtomGroupTest,
                         testing::Values(
                                 UseCase("(atom? Harry)", "bool: #t"),
                                 UseCase("(atom? (Harry ahd a heap of apples))", "bool: #f"),
                                 UseCase("(atom? (car (Harry had a heap of apples)))", "bool: #t"),
                                 UseCase("(atom? (cdr (Harry had a heap of apples)))", "bool: #f"),
                                 UseCase("(atom? (cdr (Harry)))", "bool: #f"),
                                 UseCase("(atom? (car (cdr (swing low sweet cherry oat))))", "bool: #t"),
                                 UseCase("(atom? (car (cdr (swing (low sweet) cherry oat))))", "bool: #f")
                         ));

TEST_P(IsAtomGroupTest, should_return_expected_is_atom_res_from_scheme_interpreter) {
    UseCase use_case = GetParam();

    scheme(use_case);
}
