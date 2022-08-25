#include "others.h"

s_expression* quote::execute() {
    switch (exp.type) {
        case 'A':
            return new atom{exp.value};
        case 'B':
            return new boolean{exp.value};
        case 'N':
            return new integer{exp.integer_value};
        default:
            return new atom{exp.value};
    }
}
