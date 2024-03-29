//
//  console_code.cpp
//  meta
//
//  Created by Cosmo Julis on 1/30/22.
//

#include "console_code.hpp"

namespace meta::console {

std::ostream & operator<<(std::ostream & os, const Code & c) {
    switch (c) {
        case NOP:
            os << "nop";
            break;
        case SET:
            os << "set";
            break;
        case GET:
            os << "get";
            break;
        case SHOW:
            os << "show";
            break;
        case REPEAT:
            os << "repeat";
            break;
            
        case ADD:
            os << "add";
            break;
        case SUB:
            os << "sub";
            break;
        case MUL:
            os << "mul";
            break;
        case DIV:
            os << "div";
            break;

        case EQUAL:
            os << "equal";
            break;
        case LESS:
            os << "less";
            break;
        case GREATER:
            os << "greater";
            break;
        case NOT:
            os << "not";
            break;
//        case AND:
//            os << "and";
//            break;
//        case OR:
//            os << "or";
//            break;
//        case XOR:
//            os << "xor";
//            break;

            
        case PAUSE:
            os << "pause";
            break;
        case SLEEP:
            os << "sleep";
            break;
        default:
            os << "unknown";
            break;
    }
    return os;
}

int CodeBranch(const Code & c) {
    switch (c) {
        case SET:
            return 3;
        case GET:
            return 2;
        case SHOW:
            return 1;
        case REPEAT:
            return 2;
        case ADD:
        case SUB:
        case MUL:
        case DIV:
            return 2;
        case EQUAL:
        case LESS:
        case GREATER:
            return 2;
        case NOT:
            return 1;
//        case AND:
//        case OR:
//        case XOR:
//            return 2;

        case PAUSE:
            return 0;
        case SLEEP:
            return 1;
        default:
            return 0;
    }
}

bool CodeBranchReduce(const Code & c) {
    switch (c) {
        case REPEAT:
            return false;
        default:
            return true;
    }
}

std::ostream & operator<<(std::ostream & os, const Type & t) {
    switch (t) {
        case NONE:
            os << "none";
            break;
        case INSTRUCTION:
            os << "instruction";
            break;
        case NUMBER:
            os << "number";
            break;
        case STRING:
            os << "string";
            break;
        default:
            os << "unknown";
            break;
    }
    return os;
}


}
