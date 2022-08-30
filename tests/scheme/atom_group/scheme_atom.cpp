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

TEST_P(SchemeAtomGroupTest, should_return_F_type_when_token_is_stored) {
    std::string an_atom = GetParam().input;
    is.str(an_atom);

    inter.scheme();

    ASSERT_THAT(os.str(), HasSubstr(GetParam().expected_output));
}
