//
//  console_type.cpp
//  meta
//
//  Created by Cosmo Julis on 2/10/22.
//

#include "console_type.hpp"

namespace meta::console::instruction {

std::ostream & operator<<(std::ostream & os, const Instruction & inst) {
    switch (inst) {
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

int BranchCount(const Instruction & inst) {
    switch (inst) {
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

//bool BranchNeedReduce(const Instruction & inst) {
//    switch (inst) {
//        case REPEAT:
//            return false;
//        default:
//            return true;
//    }
//}


}
