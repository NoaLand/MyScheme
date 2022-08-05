#include "list.h"


std::ostream &operator<<(std::ostream &os, const list &sl) {
    os << "( ";
    for (auto atom : sl.list) {
        os << atom.value << " ";
    }
    os << ")";

    return os;
}
