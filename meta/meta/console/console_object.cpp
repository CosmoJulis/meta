//
//  console_object.cpp
//  meta
//
//  Created by Cosmo Julis on 2/8/22.
//

#include "console_object.hpp"

namespace meta::console {

static Pool * pp = nullptr;

Pool & Pool::shared() {
    if (pp == nullptr) {
        pp = new Pool();
    }
    return *pp;
}

void Pool::clear() {
    if (pp != nullptr) delete pp;
    pp = nullptr;
}

}
