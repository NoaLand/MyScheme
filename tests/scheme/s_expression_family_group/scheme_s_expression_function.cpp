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

class IsEqGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(IsEqGroup,
                         IsEqGroupTest,
                         testing::Values(
                                 UseCase("(eq? Harry Harry)", "bool: #t"),
                                 UseCase("(eq? margarine butter)", "bool: #f"),
                                 UseCase("(eq? () (strawberry))", "bool: #f"),
                                 UseCase("(eq? 6 7)", "bool: #f"),
                                 UseCase("(eq? (car (Mary had a little lamb chop)) Mary)", "bool: #t"),
                                 UseCase("(eq? (cdr (soured milk)) milk)", "bool: #f"),
                                 UseCase("(eq? (car (beans beans we need jelly beans))"
                                                 "(car (cdr (beans beans we need jelly beans))))", "bool: #t")
                         ));

TEST_P(IsEqGroupTest, should_return_expected_is_eq_res_from_scheme_interpreter) {
    UseCase use_case = GetParam();

    scheme(use_case);
}
