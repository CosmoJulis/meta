//
//  console_code.cpp
//  meta
//
//  Created by Cosmo Julis on 1/30/22.
//

#include "console_code.hpp"

using namespace meta::console;

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
        case PAUSE:
            os << "pause";
            break;
        default:
            os << "unknown";
            break;
    }
    return os;
}
