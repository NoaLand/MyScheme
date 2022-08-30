#include "scheme/scheme_use_case.h"

class SchemeListGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(ListGroup,
                         SchemeListGroupTest,
                         testing::Values(
                                 UseCase<list<atom>>("(atom)", "( atom )"),
                                 UseCase<list<atom>>("(atom turkey or)", "( atom turkey or )"),
                                 UseCase<list<s_expression>>("((atom turkey) or)", "( ( atom turkey ) or )"),
                                 UseCase<list<s_expression>>("((x y) z)", "( ( x y ) z )"),
                                 UseCase<list<atom>>("(how are you doing so far)", "( how are you doing so far )"),
                                 UseCase<list<s_expression>>("(((how) are) ((you) (doing so)) far)", "( ( ( how ) are ) ( ( you ) ( doing so ) ) far )"),
                                 UseCase<list<integer>>("()", "( )"),
                                 UseCase<list<s_expression>>("(() () () ())", "( ( ) ( ) ( ) ( ) )")
                         ));

TEST_P(SchemeListGroupTest, should_return_expected_list_from_scheme_interpreter) {
    UseCase use_case = GetParam();

    scheme(use_case);
}
