#include "function/nor_logic_family.h"

boolean* or_logic::execute() {
    if(left->val()) {
        execute_res = new boolean{true};
    } else {
        execute_res = new boolean{right->val()};
    }

    return execute_res;
}

boolean* and_logic::execute() {
    execute_res = new boolean(left->val() && right->val());

    return execute_res;
}
