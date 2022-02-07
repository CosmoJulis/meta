//
//  console_instruction.cpp
//  meta
//
//  Created by Cosmo Julis on 2/7/22.
//

#include "console_instruction.hpp"
#include "console_manager.hpp"

namespace meta::console {

void Instruction::pop() {
    for (const auto & reg : _regs) {
        if (reg.type() == INSTRUCTION) {
            Manager::shared()._map.remove(reg.get_inst_id());
        }
    }
}

}
