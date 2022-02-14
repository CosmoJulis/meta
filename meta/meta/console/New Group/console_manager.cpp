//
//  console_manager.cpp
//  meta
//
//  Created by Cosmo Julis on 2/5/22.
//

#include "console_manager.hpp"

namespace meta::console {

Instruction & Stack::top_inst() {
    if (_stack.size() > 0) {
        return Manager::shared()._map.get(_stack.top());
    } else {
        throw "Missing instruction.";
    }
}

void Queue::pop() {
    auto & inst_id = front();
    if (!Manager::shared()._map.remove(inst_id)) {
        throw "Pop instruction index not exist.";
    }
    _queue.pop();
}


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
