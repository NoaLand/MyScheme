#include "runnable_the_little_schemer//scheme_use_case.h"

class CarFunctionGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(CarGroup,
                         CarFunctionGroupTest,
                         testing::Values(
                                 UseCase<atom>("(car (a b c))", "a"),
                                 UseCase<list<atom>>("(car ((a b c) x y z))", "( a b c )"),
                                 UseCase<list<atom>>("(car (((hotdogs)) (and) (pickle) relish))", "( ( hotdogs ) )"),
                                 UseCase<list<atom>>("(car (car (((hotdogs)) (and))))", "( hotdogs )"),
                                 UseCase<list<atom>>("(car hotdog)", "should throw! car is only for list", true),
                                 UseCase<list<atom>>("(car ())", "should throw! car is only for list", true)
                         ));

TEST_P(CarFunctionGroupTest, should_return_expected_car_res_from_scheme_interpreter) {
    UseCase use_case = GetParam();

    scheme(use_case);
}

class CdrFunctionGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(CdrGroup,
                         CdrFunctionGroupTest,
                         testing::Values(
                                 UseCase<list<atom>>("(cdr ((a b c) x y z))", "( x y z )"),
                                 UseCase<list<integer>>("(cdr (hamburger))", "( )"),
                                 UseCase<list<atom>>("(cdr ((x) t r))", "( t r )"),
                                 UseCase<list<atom>>("(cdr hotdogs)", "should throw! cdr is only for list", true),
                                 UseCase<list<atom>>("(cdr ())", "should throw! cdr is only for list", true)
                         ));

TEST_P(CdrFunctionGroupTest, should_return_expected_cdr_res_from_scheme_interpreter) {
    UseCase use_case = GetParam();

    scheme(use_case);
}

class CarCdrFunctionGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(CarCdrGroup,
                         CarCdrFunctionGroupTest,
                         testing::Values(
                                 UseCase<list<atom>>("(car (cdr ((b) (x y) (c))))", "( x y )"),
                                 UseCase<list<atom>>("(cdr (cdr ((b) (x y) ((c)))))", "( ( ( c ) ) )"),
                                 UseCase<list<atom>>("(cdr (car (a (b (c)) d)))", "should throw! car should take a list!", true)
                         ));

TEST_P(CarCdrFunctionGroupTest, should_return_expected_mix_car_cdr_res_from_scheme_interpreter) {
    UseCase use_case = GetParam();

    scheme(use_case);
}

class ConsFunctionGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(ConsGroup,
                         ConsFunctionGroupTest,
                         testing::Values(
                                 UseCase<list<atom>>("(cons peanut (butter and jelly))", "( peanut butter and jelly )"),
                                 UseCase<list<s_expression>>("(cons (banana and) (peanut butter and jelly))", "( ( banana and ) peanut butter and jelly )"),
                                 UseCase<list<s_expression>>("(cons ((help) this) (is very ((hard) to learn)))", "( ( ( help ) this ) is very ( ( hard ) to learn ) )"),
                                 UseCase<list<s_expression>>("(cons (a b (c)) ())", "( ( a b ( c ) ) )"),
                                 UseCase<list<atom>>("(cons a ())", "( a )"),
                                 UseCase<list<atom>>("(cons ((a b c)) b)", "should throw! cons second param needs a list type!", true),
                                 UseCase<list<atom>>("(cons a b)", "should throw! cons second param needs a list type", true),
                                 UseCase<list<atom>>("(cons a (car ((b) c d)))", "( a b )"),
                                 UseCase<list<atom>>("(cons a (cdr ((b) c d)))", "( a c d )")
                         ));

TEST_P(ConsFunctionGroupTest, should_return_expected_cons_res_from_scheme_interpreter) {
    UseCase use_case = GetParam();

    scheme(use_case);
}

class IsNullFunctionGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(IsNullGroup,
                         IsNullFunctionGroupTest,
                         testing::Values(
                                 UseCase<boolean>("(null? ())", "#t"),
                                 UseCase<boolean>("(null? (a b c))", "#f"),
                                 UseCase<boolean>("(null? spaghetti)", "should throw! null? take a list as param", true)
                         ));

TEST_P(IsNullFunctionGroupTest, should_return_expected_is_null_res_from_scheme_interpreter) {
    UseCase use_case = GetParam();

    scheme(use_case);
}

class AddTupGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(AddTupGroup,
                         AddTupGroupTest,
                         testing::Values(
                                 UseCase<integer>("(addtup (3 5 2 8))", "18"),
                                 UseCase<integer>("(addtup (15 6 7 12 3))", "43")
                         ));

TEST_P(AddTupGroupTest, should_return_expected_add_tup_res_from_scheme_interpreter) {
    UseCase use_case = GetParam();

    scheme(use_case);
}

class TupAddGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(TupAddGroup,
                         TupAddGroupTest,
                         testing::Values(
                                 UseCase<list<integer>>("(tup+ (3 6 9 11 4) (8 5 2 0 7))", "( 11 11 11 11 11 )"),
                                 UseCase<list<integer>>("(tup+ (2 3) (4 6))", "( 6 9 )"),
                                 UseCase<list<integer>>("(tup+ (3 7) (4 6))", "( 7 13 )"),
                                 UseCase<list<integer>>("(tup+ (3 7) (4 6 8 1))", "should throw! tup+ need tuples and has same size!", true)
                         ));

TEST_P(TupAddGroupTest, should_return_expected_add_tup_res_from_scheme_interpreter) {
    function_define("+", "(define + (lambda (n m) (cond ((zero? m) n) (else (add1 (+ n (sub1 m)))))))");
    function_define("tup+", "(define tup+ (lambda (tup1 tup2) (cond ((and? (null? tup1) (null? tup2)) ()) (else (cons (+ (car tup1) (car tup2)) (tup+ (cdr tup1) (cdr tup2)))))))");
    UseCase use_case = GetParam();

    scheme(use_case);
}

class TupAddV2GroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(TupAddV2Group,
                         TupAddV2GroupTest,
                         testing::Values(
                                 UseCase<list<integer>>("(tup+ (3 6 9 11 4) (8 5 2 0 7))", "( 11 11 11 11 11 )"),
                                 UseCase<list<integer>>("(tup+ (2 3) (4 6))", "( 6 9 )"),
                                 UseCase<list<integer>>("(tup+ (3 7) (4 6))", "( 7 13 )"),
                                 UseCase<list<integer>>("(tup+ (3 7) (4 6 8 1))", "( 7 13 8 1 )")
                         ));

TEST_P(TupAddV2GroupTest, should_return_expected_add_tup_v2_res_from_scheme_interpreter) {
    function_define("+", "(define + (lambda (n m) (cond ((zero? m) n) (else (add1 (+ n (sub1 m)))))))");
    function_define("tup+", "(define tup+ (lambda (tup1 tup2) (cond ((null? tup1) tup2) ((null? tup2) tup1) (else (cons (+ (car tup1) (car tup2)) (tup+ (cdr tup1) (cdr tup2)))))))");
    UseCase use_case = GetParam();

    scheme(use_case);
}

class LengthGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(LengthGroup,
                         LengthGroupTest,
                         testing::Values(
                                 UseCase<integer>("(length (hotdogs with mustard sauerkraut and pickles))", "6"),
                                 UseCase<integer>("(length (ham and cheese on rye))", "5")
                         ));

TEST_P(LengthGroupTest, should_return_expected_length_res_from_scheme_interpreter) {
    function_define("length", "(define length (lambda (lat) (cond ((null? lat) 0) (else (add1 (length (cdr lat)))))))");
    UseCase use_case = GetParam();

    scheme(use_case);
}

class PickGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(PickGroup,
                         PickGroupTest,
                         testing::Values(
                                 UseCase<atom>("(pick 4 (lasagna spaghetti ravioli macaroni meatball))", "macaroni"),
                                 UseCase<atom>("(pick 0 (lasagna spaghetti ravioli macaroni meatball))", "should throw! cannot pick 0 from list!", true)
                         ));

TEST_P(PickGroupTest, should_return_expected_pick_res_from_scheme_interpreter) {
    function_define("pick", "(define pick (lambda (n lat) (cond ((zero? (sub1 n)) (car lat)) (else (pick (sub1 n) (cdr lat))))))");
    UseCase use_case = GetParam();

    scheme(use_case);
}

class RemPickGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(RemPickGroup,
                         RemPickGroupTest,
                         testing::Values(
                                 UseCase<list<atom>>("(rempick 3 (hotdogs with hot mustard))", "( hotdogs with mustard )")
                         ));

TEST_P(RemPickGroupTest, should_return_expected_rempick_res_from_scheme_interpreter) {
    function_define("rempick", "(define rempick (lambda (n lat) (cond ((zero? (sub1 n)) (cdr lat)) (else (cons (car lat) (rempick (sub1 n) (cdr lat)))))))");
    UseCase use_case = GetParam();

    scheme(use_case);
}

TEST_P(RemPickGroupTest, should_return_expected_rempick_v2_res_from_scheme_interpreter) {
    function_define("=", "(define = (lambda (n m) (cond ((and? (zero? n) (zero? m)) #t) ((or? (zero? n) (zero? m)) #f) (else (= (sub1 n) (sub1 m))))))");
    function_define("one?", "(define one?  (lambda (n) (= n 1)))");
    function_define("rempick", "(define rempick (lambda (n lat) (cond ((one? n) (cdr lat)) (else (cons (car lat) (rempick (sub1 n) (cdr lat)))))))");
    UseCase use_case = GetParam();

    scheme(use_case);
}

class IsSetGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(IsSetGroup,
                         IsSetGroupTest,
                         testing::Values(
                                 UseCase<boolean>("(set? (apple peaches apple plum))", "#f"),
                                 UseCase<boolean>("(set? (apple peaches pears plums))", "#t"),
                                 UseCase<boolean>("(set? ())", "#t"),
                                 UseCase<boolean>("(set? (apple 3 pear 4 9 apple 3 4))", "#f")
                         ));

TEST_P(IsSetGroupTest, should_return_expected_isset_boolean_res_from_scheme_interpreter) {
    function_define("member?", "(define member?  (lambda (a lat) (cond ((null? lat) #f) (else (or? (eq? (car lat) a) (member? a (cdr lat)))))))");
    function_define("set?", "(define set? (lambda (lat) (cond ((null? lat) #t) ((member? (car lat) (cdr lat)) #f) (else (set? (cdr lat)))))) ");

    UseCase use_case = GetParam();
    scheme(use_case);
}

class MakeSetV1GroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(MakeSetGroup,
                         MakeSetV1GroupTest,
                         testing::Values(
                                 UseCase<list<atom>>("(makeset (apple peach pear peach plum apple lemon peach))", "( pear plum apple lemon peach )")
                         ));

TEST_P(MakeSetV1GroupTest, should_return_expected_makeset_boolean_res_from_scheme_interpreter) {
    function_define("member?", "(define member?  (lambda (a lat) (cond ((null? lat) #f) (else (or? (eq? (car lat) a) (member? a (cdr lat)))))))");
    function_define("makeset", "(define makeset (lambda (lat) (cond ((null? lat) ()) ((member? (car lat) (cdr lat)) (makeset (cdr lat))) (else (cons (car lat) (makeset (cdr lat)))))))");

    UseCase use_case = GetParam();
    scheme(use_case);
}

class MakeSetV2GroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(MakeSetGroup,
                         MakeSetV2GroupTest,
                         testing::Values(
                                 UseCase<list<atom>>("(makeset (apple peach pear peach plum apple lemon peach))", "( apple peach pear plum lemon )"),
                                 UseCase<list<s_expression>>("(makeset (apple 3 pear 4 9 apple 3 4))", "( apple 3 pear 4 9 )")
                         ));

TEST_P(MakeSetV2GroupTest, should_return_expected_makeset_boolean_res_from_scheme_interpreter) {
    function_define("multirember", "(define multirember (lambda (a lat) (cond ((null? lat) ()) ((eq? a (car lat)) (multirember a (cdr lat))) (else (cons (car lat) (multirember a (cdr lat)))))))");
    function_define("makeset", "(define makeset (lambda (lat) (cond ((null? lat) ()) (else (cons (car lat) (makeset (multirember (car lat) (cdr lat))))))))");

    UseCase use_case = GetParam();
    scheme(use_case);
}

class IsSubSetGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(IsSubSetGroup,
                         IsSubSetGroupTest,
                         testing::Values(
                                 UseCase<boolean>("(subset? (5 chicken wings) (5 hamburgers 2 pieces fried chicken and light duckling wings))", "#t"),
                                 UseCase<boolean>("(subset? (4 pounds of horseradish) (four pounds chicken and 5 ounces horseradish))", "#f")
                         ));

TEST_P(IsSubSetGroupTest, should_return_expected_issubset_v1_boolean_res_from_scheme_interpreter) {
    function_define("member?", "(define member?  (lambda (a lat) (cond ((null? lat) #f) (else (or? (eq? (car lat) a) (member? a (cdr lat)))))))");
    function_define("subset?", "(define subset?  (lambda (set1 set2) (cond ((null? set1) #t) ((member? (car set1) set2) (subset? (cdr set1) set2)) (else #f))))");

    UseCase use_case = GetParam();
    scheme(use_case);
}

TEST_P(IsSubSetGroupTest, should_return_expected_issubset_v2_boolean_res_from_scheme_interpreter) {
    function_define("member?", "(define member?  (lambda (a lat) (cond ((null? lat) #f) (else (or? (eq? (car lat) a) (member? a (cdr lat)))))))");
    function_define("subset?", "(define subset? (lambda (set1 set2) (cond ((null? set1) #t) (else (and? (member? (car set1) set2) (subset? (cdr set1) set2))))))");

    UseCase use_case = GetParam();
    scheme(use_case);
}

class IsSetEqGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(IsSetEqGroup,
                         IsSetEqGroupTest,
                         testing::Values(
                                 UseCase<boolean>("(eqset? (6 large chickens with wings) (6 chickens with large wings))", "#t"),
                                 UseCase<boolean>("(eqset? (5 a x s) (x s 5 a))", "#t"),
                                 UseCase<boolean>("(eqset? (2a b c d) (2 a b c d))", "#f")
                         ));

TEST_P(IsSetEqGroupTest, should_return_expected_issubset_v1_boolean_res_from_scheme_interpreter) {
    function_define("member?", "(define member?  (lambda (a lat) (cond ((null? lat) #f) (else (or? (eq? (car lat) a) (member? a (cdr lat)))))))");
    function_define("subset?", "(define subset?  (lambda (set1 set2) (cond ((null? set1) #t) ((member? (car set1) set2) (subset? (cdr set1) set2)) (else #f))))");
    function_define("eqset?", "(define eqset? (lambda (set1 set2) (and? (subset? set1 set2) (subset? set2 set1))))");

    UseCase use_case = GetParam();
    scheme(use_case);
}
