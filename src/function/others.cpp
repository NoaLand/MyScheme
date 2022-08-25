#include "function/others.h"

atom* quote::execute() {
    return new atom{exp->get_value()};
}
