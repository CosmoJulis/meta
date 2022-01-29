//
//  console_run.cpp
//  meta
//
//  Created by Cosmo Julis on 1/29/22.
//

#include "console_run.hpp"
#include "console_instruction.hpp"

namespace meta::console {

void run(Stack & s) {
    while (s.size() > 0) {
        std::stack<Reg> inst_stack;
        
        Reg r;
        do {
            r = s.pop();
            inst_stack.push(r);
        } while (r.type != INSTRUCTION);
        
        r = inst_stack.top();
        inst_stack.pop();
        switch (r.code) {
            case NOP:
                break;
            case SET:
                Set(inst_stack).execute();
                break;
            case GET:
                Get(inst_stack).execute();
                break;
            case SHOW:
                Show(inst_stack).execute();
                break;
            case REPEAT:
                break;
            default:
                break;
        }
        
    }
}

}
