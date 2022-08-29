#include "preload_libs/preload_libs.h"

auto preload_libs(function_context &context) -> void {
    auto lat_params = new list<param>();
    lat_params->push_back(new param{"l"});
    auto lat = new function_declaration(
            "lat?",
            lat_params,
            "(cond ( ( null? $l$ ) #t ) ( ( atom? ( car $l$ ) ) ( lat? ( cdr $l$ ) ) ) ( else #f ) )"
    );

    auto lat_length_params = new list<param>();
    lat_length_params->push_back(new param{"lat"});
    auto lat_length = new function_declaration(
            "length",
            lat_length_params,
            "(cond ( ( null? $lat$ ) 0 ) ( else ( add1 ( length ( cdr $lat$ ) ) ) ) )"
    );

    auto is_member_params = new list<param>();
    is_member_params->push_back(new param{"a"});
    is_member_params->push_back(new param{"lat"});
    auto is_member = new function_declaration(
            "member?",
            is_member_params,
            "(cond ( ( null? $lat$ ) #f ) ( else ( or ( eq? ( car $lat$ ) $a$ ) ( member? $a$ ( cdr $lat$ ) ) ) ) ) "
    );

    auto rember_params = new list<param>();
    rember_params->push_back(new param{"a"});
    rember_params->push_back(new param{"lat"});
    auto rember = new function_declaration(
            "rember",
            rember_params,
            "(cond ( ( null? $lat$ ) ( ( ) ) ) ( else ( cond ( ( eq? ( car $lat$ ) $a$ ) ( cdr $lat$ ) ) ( else ( cons ( car $lat$ ) ( rember $a$ ( cdr $lat$ ) ) ) ) ) ) ) "
    );

    auto pick_params = new list<param>();
    pick_params->push_back(new param{"n"});
    pick_params->push_back(new param{"lat"});
    auto pick = new function_declaration(
            "pick",
            pick_params,
            "(cond ( ( zero? ( sub1 $n$ ) ) ( car $lat$ ) ) ( else ( pick ( sub1 $n$ ) ( cdr $lat$ ) ) ) )"
    );

    auto rempick_params = new list<param>();
    rempick_params->push_back(new param{"n"});
    rempick_params->push_back(new param{"lat"});
    auto rempick = new function_declaration(
            "rempick",
            rempick_params,
            "(cond ( ( zero? ( sub1 $n$ ) ) ( cdr $lat$ ) ) ( else ( cons ( car $lat$ ) ( rempick ( sub1 $n$ ) ( cdr $lat$ ) ) ) ) )"
    );

    auto add_params = new list<param>();
    add_params->push_back(new param{"n"});
    add_params->push_back(new param{"m"});
    auto add = new function_declaration(
            "+",
            add_params,
            "(cond ( ( zero? $m$ ) $n$ ) ( else ( add1 ( + $n$ ( sub1 $m$ ) ) ) ) )"
    );

    auto sub_params = new list<param>();
    sub_params->push_back(new param{"n"});
    sub_params->push_back(new param{"m"});
    auto sub = new function_declaration(
            "-",
            sub_params,
            "(cond ( ( zero? $m$ ) $n$ ) ( else ( sub1 ( - $n$ ( sub1 $m$ ) ) ) ) )"
    );

    auto multiplication_params = new list<param>();
    multiplication_params->push_back(new param{"n"});
    multiplication_params->push_back(new param{"m"});
    auto multiplication = new function_declaration(
            "*",
            multiplication_params,
            "(cond ( ( zero? $m$ ) 0 ) ( else ( + $n$ ( * $n$ ( sub1 $m$ ) ) ) ) )"
    );

    auto divide_params = new list<param>();
    divide_params->push_back(new param{"n"});
    divide_params->push_back(new param{"m"});
    auto divide = new function_declaration(
            "/",
            divide_params,
            "(cond ( ( < $n$ $m$ ) 0 ) ( else ( add1 ( / ( - $n$ $m$ ) $m$ ) ) ) )"
    );

    auto greater_than_params = new list<param>();
    greater_than_params->push_back(new param{"n"});
    greater_than_params->push_back(new param{"m"});
    auto greater_than = new function_declaration(
            ">",
            greater_than_params,
            "(cond ( ( zero? $n$ ) #f ) ( ( zero? $m$ ) #t ) ( else ( > ( sub1 $n$ ) ( sub1 $m$ ) ) ) )"
    );

    auto less_than_params = new list<param>();
    less_than_params->push_back(new param{"n"});
    less_than_params->push_back(new param{"m"});
    auto less_than = new function_declaration(
            "<",
            less_than_params,
            "(cond ( ( zero? $m$ ) #f ) ( ( zero? $n$ ) #t ) ( else ( < ( sub1 $n$ ) ( sub1 $m$ ) ) ) )"
    );

    auto equal_params = new list<param>();
    equal_params->push_back(new param{"n"});
    equal_params->push_back(new param{"m"});
    auto equal = new function_declaration(
            "=",
            equal_params,
            "(cond ( ( > $n$ $m$ ) #f ) ( ( < $n$ $m$ ) #f ) ( else #t ) )"
    );

    auto expt_params = new list<param>();
    expt_params->push_back(new param{"n"});
    expt_params->push_back(new param{"m"});
    auto expt = new function_declaration(
            "^",
            expt_params,
            "(cond ( ( zero? $m$ ) 1 ) ( else ( * $n$ ( ^ $n$ ( sub1 $m$ ) ) ) ) )"
    );

    context.store(lat);
    context.store(lat_length);
    context.store(is_member);
    context.store(rember);
    context.store(pick);
    context.store(rempick);
    context.store(add);
    context.store(sub);
    context.store(multiplication);
    context.store(divide);
    context.store(greater_than);
    context.store(less_than);
    context.store(equal);
    context.store(expt);
}
