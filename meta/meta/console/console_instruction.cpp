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
    

    std::vector<Reg> tmpBranchs = _branchs;
    size_t count = tmpBranchs.size();
    
    if (CodeBranchReduce(code)) {
        for (int index = 0; index < count; index++) {
            while (tmpBranchs[index].type() == INSTRUCTION) {
                InstID id = tmpBranchs[index].get_inst_id();
                auto & inst = Manager::shared()._map.get(id);
                tmpBranchs[index] = inst.execute();
            }
        }
    }
    
    switch (code) {
        case SET: {
            auto & obj = Pool::shared().find(tmpBranchs[0]);
            if (tmpBranchs[1].type() != STRING) {
                throw "Key must be string.";
            }
            obj.set(tmpBranchs[1].get_string(), tmpBranchs[2]);
            return Reg::PLACE();
        }
        case GET: {
            auto & obj = Pool::shared().find(tmpBranchs[0]);
            if (tmpBranchs[1].type() != STRING) {
                throw "Key must be string.";
            }
            return obj.get(tmpBranchs[1].get_string());
        }
        case SHOW:
            if (tmpBranchs[0].type() == STRING) {
                std::cout << tmpBranchs[0].get_string() << std::endl;
            }
            else if (tmpBranchs[0].type() == NUMBER) {
                std::cout << tmpBranchs[0].get_number() << std::endl;
            }
            else {
                throw "Show value not supported.";
            }
            return Reg::PLACE();
        case REPEAT: {
            while (tmpBranchs[0].type() == INSTRUCTION) {
                InstID id = _branchs[0].get_inst_id();
                auto & inst = Manager::shared()._map.get(id);
                tmpBranchs[0] = inst.execute();
            }
            
            if (tmpBranchs[0].type() != NUMBER) {
                throw "Repeat count not supported.";
            }
            int count = tmpBranchs[0].get_number();

            if (tmpBranchs[1].type() != INSTRUCTION) {
                throw "Repeat is missing instruction.";
            }
            
            InstID id = tmpBranchs[1].get_inst_id();
            auto & inst = Manager::shared()._map.get(id);
            
            for (int i = 0; i < count; i++) {
                inst.execute();
            }
            
            return Reg::PLACE();
        }
        case ADD: {
            if (tmpBranchs[0].type() != NUMBER || tmpBranchs[1].type() != NUMBER) {
                throw "Add must be number.";
            }
            Reg r;
            r.set(tmpBranchs[0].get_number() + tmpBranchs[1].get_number());
            return r;
        }
        case SUB: {
            if (tmpBranchs[0].type() != NUMBER || tmpBranchs[1].type() != NUMBER) {
                throw "Sub must be number.";
            }
            Reg r;
            r.set(tmpBranchs[0].get_number() - tmpBranchs[1].get_number());
            return r;
        }
        case MUL: {
            if (tmpBranchs[0].type() != NUMBER || tmpBranchs[1].type() != NUMBER) {
                throw "Mul must be number.";
            }
            Reg r;
            r.set(tmpBranchs[0].get_number() * tmpBranchs[1].get_number());
            return r;
        }
        case DIV: {
            if (tmpBranchs[0].type() != NUMBER || tmpBranchs[1].type() != NUMBER) {
                throw "Div must be number.";
            }
            Reg r;
            r.set(tmpBranchs[0].get_number() / tmpBranchs[1].get_number());
            return r;
        }
        case EQUAL: {
            if (tmpBranchs[0].type() != NUMBER || tmpBranchs[1].type() != NUMBER) {
                throw "Less must be number.";
            }
            Reg r;
            r.set(tmpBranchs[0].get_number() == tmpBranchs[1].get_number());
            return r;
        }
        case LESS: {
            if (tmpBranchs[0].type() != NUMBER || tmpBranchs[1].type() != NUMBER) {
                throw "Less must be number.";
            }
            Reg r;
            r.set(tmpBranchs[0].get_number() < tmpBranchs[1].get_number());
            return r;
        }
        case GREATER: {
            if (tmpBranchs[0].type() != NUMBER || tmpBranchs[1].type() != NUMBER) {
                throw "Greater must be number.";
            }
            Reg r;
            r.set(tmpBranchs[0].get_number() > tmpBranchs[1].get_number());
            return r;
        }
        case NOT: {
            if (tmpBranchs[0].type() != NUMBER) {
                throw "Not must be number.";
            }
            Reg r;
            r.set(!(tmpBranchs[0].get_number()));
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
