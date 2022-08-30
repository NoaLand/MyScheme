#include "scheme/scheme_use_case.h"

class SchemeListGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(ListGroup,
                         SchemeListGroupTest,
                         testing::Values(
                                 UseCase("(atom)", "list: ( atom )"),
                                 UseCase("(atom turkey or)", "list: ( atom turkey or )"),
                                 UseCase("((atom turkey) or)", "list: ( ( atom turkey ) or )"),
                                 UseCase("((x y) z)", "list: ( ( x y ) z )"),
                                 UseCase("(how are you doing so far)", "list: ( how are you doing so far )"),
                                 UseCase("(((how) are) ((you) (doing so)) far)", "list: ( ( ( how ) are ) ( ( you ) ( doing so ) ) far )"),
                                 UseCase("()", "tuple: ( )"),
                                 UseCase("(() () () ())", "list: ( ( ) ( ) ( ) ( ) )")
                         ));

TEST_P(SchemeListGroupTest, should_return_expected_list_from_scheme_interpreter) {
    UseCase use_case = GetParam();

    scheme(use_case);
}
