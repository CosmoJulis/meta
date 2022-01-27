//
//  vm_instruction.hpp
//  meta
//
//  Created by Cosmo Julis on 1/21/22.
//

#ifndef vm_instruction_hpp
#define vm_instruction_hpp

namespace meta::vm {



enum instruction : unsigned char {
    push,
    pop,
    show,
    pause,
    play,
    step,
    repeat,
    clear,
};




}

#endif /* vm_instruction_hpp */
