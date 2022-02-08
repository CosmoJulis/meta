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
            while (_branchs[index].type() == INSTRUCTION) {
                int inst_id = _branchs[index].get_inst_id();
                auto & inst = Manager::shared()._map.get(inst_id);
                _branchs[index] = inst.execute();
                Manager::shared()._map.remove(inst_id);
            }
        }
    }
    
    switch (code) {
        case SET: {
            auto & obj = Pool::shared().find(_branchs[0]);
            if (_branchs[1].type() != STRING) {
                throw "Key must be string.";
            }
            obj.set(_branchs[1].get_string(), _branchs[2]);
            return Reg::PLACE();
        }
        case GET: {
            auto & obj = Pool::shared().find(_branchs[0]);
            if (_branchs[1].type() != STRING) {
                throw "Key must be string.";
            }
            return obj.get(_branchs[1].get_string());
        }
        case SHOW:
            if (_branchs[0].type() == STRING) {
                std::cout << _branchs[0].get_string() << std::endl;
            }
            else if (_branchs[0].type() == NUMBER) {
                std::cout << _branchs[0].get_number() << std::endl;
            }
            else {
                throw "Show value not supported.";
            }
            return Reg::PLACE();
        case REPEAT: {
            while (_branchs[0].type() == INSTRUCTION) {
                int inst_id = _branchs[0].get_inst_id();
                auto & inst = Manager::shared()._map.get(inst_id);
                _branchs[0] = inst.execute();
                Manager::shared()._map.remove(inst_id);
            }
            
            if (_branchs[0].type() != NUMBER) {
                throw "Repeat count not supported.";
            }
            int count = _branchs[0].get_number();

            if (_branchs[1].type() != INSTRUCTION) {
                throw "Repeat is missing instruction.";
            }
            
            int inst_id = _branchs[1].get_inst_id();
            auto & inst = Manager::shared()._map.get(inst_id);
            
            for (int i = 0; i < count; i++) {
                inst.execute();
            }
            Manager::shared()._map.remove(inst_id);
            
            return Reg::PLACE();
        }
            
        case ADD: {
            if (_branchs[0].type() != NUMBER || _branchs[1].type() != NUMBER) {
                throw "Add must be number.";
            }
            Reg r;
            r.set(_branchs[0].get_number() + _branchs[1].get_number());
            return r;
        }
            
        case PAUSE:
            
            break;
        default:
            break;
    }
    
    return Reg::PLACE();
}

}
