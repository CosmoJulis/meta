//
//  console_parser.cpp
//  meta
//
//  Created by Cosmo Julis on 2/9/22.
//

#include "console_parser.hpp"

namespace meta::console {

static Parser * pp = nullptr;

Parser & Parser::shared() {
    if (pp == nullptr) {
        pp = new Parser();
    }
    return *pp;
}

void Parser::clear() {
    if (pp != nullptr) delete pp;
    pp = nullptr;
}


}
