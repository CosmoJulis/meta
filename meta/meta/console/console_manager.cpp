//
//  console_manager.cpp
//  meta
//
//  Created by Cosmo Julis on 2/5/22.
//

#include "console_manager.hpp"

namespace meta::console {

static Manager * pm = nullptr;

Manager & Manager::shared() {
    if (pm == nullptr) {
        pm = new Manager();
    }
    return *pm;
}

void Manager::clear() {
    if (pm != nullptr) delete pm;
    pm = nullptr;
}

}
