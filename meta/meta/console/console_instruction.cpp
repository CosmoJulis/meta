//
//  console_instruction.cpp
//  meta
//
//  Created by Cosmo Julis on 2/7/22.
//

#include "console_instruction.hpp"
#include "console_manager.hpp"
#include "console_object.hpp"

namespace meta::console {

void Instruction::pop() {
    for (const auto & b : _branchs) {
        if (b.type() == INSTRUCTION) {
            Manager::shared()._map.remove(b.get_inst_id());
        }
    }
}

Reg Instruction::execute() {
    
    if (_branchs.size() != CodeBranch(code)) {
        throw "Instruction branch count not match.";
    }
    
    if (CodeBranchReduce(code)) {
        size_t count = _branchs.size();
        for (int index = 0; index < count; index++) {
            if (_branchs[index].type() == INSTRUCTION) {
                auto & inst = Manager::shared()._map.get(_branchs[index].get_inst_id());
                _branchs[index] = inst.execute();
            }
        }
    }
    
    switch (code) {
        case SET:
            auto & obj = Object::find(_branchs[0]);
            if (_branchs[1].type() != STRING) {
                throw "Key must be string.";
            }
            obj.set(_branchs[1].get_string(), _branchs[2]);
            return <#expression#>;
        case GET:
            if (_branchs.front().type() == NUMBER) {
                auto & obj = Object::find(int(_branchs.front().get_number()));
                // return obj get name
            }
            else if (_branchs.front().type() == STRING) {
                auto & obj = Object::find(int(_branchs.front().get_number()));
                // return obj get name
            }
            break;
        case SHOW:
            
            break;
        case REPEAT:
            
            break;
        case PAUSE:
            
            break;
        default:
            break;
    }
}

}
