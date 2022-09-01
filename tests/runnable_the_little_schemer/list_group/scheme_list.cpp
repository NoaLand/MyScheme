#include "runnable_the_little_schemer//scheme_use_case.h"

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


class TupleGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(TupleGroup,
                         TupleGroupTest,
                         testing::Values(
                                 UseCase<list<integer>>("(2 11 3 79 47 6)", "( 2 11 3 79 47 6 )"),
                                 UseCase<list<integer>>("(8 55 5 555)", "( 8 55 5 555 )"),
                                 UseCase<list<atom>>("(1 2 8 apple 4 3)", "( 1 2 8 apple 4 3 )"),
                                 UseCase<list<s_expression>>("(3 (7 4) 13 9)", "( 3 ( 7 4 ) 13 9 )"),
                                 UseCase<list<integer>>("()", "( )")
                         ));

TEST_P(TupleGroupTest, should_return_tuple_from_scheme_interpreter) {
    UseCase<s_expression> use_case = GetParam();

    scheme(use_case);
}

class PairFirstGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(PairFirstGroup,
                         PairFirstGroupTest,
                         testing::Values(
                                 UseCase<atom>("(first (a b))", "a"),
                                 UseCase<list<atom>>("(first ((a) b))", "( a )"),
                                 UseCase<list<atom>>("(first ((a b) (c d)))", "( a b )")
                         ));

TEST_P(PairFirstGroupTest, should_return_pair_first_s_expression_in_list_from_scheme_interpreter) {
    function_define("first", "(define first (lambda (p) (car p)))");
    UseCase<s_expression> use_case = GetParam();

    scheme(use_case);
}