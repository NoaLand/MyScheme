#include "function/others.h"

atom* quote::execute() {
    execute_res = new atom{exp->get_value()};

    return execute_res;
}
