//
//  console_manager.cpp
//  meta
//
//  Created by Cosmo Julis on 1/30/22.
//

#include "console_manager.hpp"
#include "console_instruction.hpp"

using namespace meta::console;

void Manager::perform(Statement & st) {
    while (st.size() > 0) {
//        std::stack<Reg> inst_stack;
//
//        Reg r;
//        do {
//            r = s.pop();
//            inst_stack.push(r);
//        } while (r.type != INSTRUCTION);
//
//        r = inst_stack.top();
//        inst_stack.pop();
//        switch (r.code) {
//            case NOP:
//                break;
//            case SET:
//                Set(inst_stack).execute();
//                break;
//            case GET:
//                Get(inst_stack).execute();
//                break;
//            case SHOW:
//                Show(inst_stack).execute();
//                break;
//            case REPEAT:
//                break;
//            default:
//                break;
//        }
    }
}
