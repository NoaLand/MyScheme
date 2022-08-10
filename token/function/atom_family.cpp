#include "atom_family.h"
#include "../s_expression/atom.h"

s_expression *is_atom::execute() {
    if(s_exp->get_indicator() == "atom") {
        return new atom{"#t"};
    } else {
        return new atom{"#f"};
    }
}
