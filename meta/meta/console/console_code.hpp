//
//  console_code.hpp
//  meta
//
//  Created by Cosmo Julis on 1/30/22.
//

#ifndef console_code_hpp
#define console_code_hpp

#include <iostream>

namespace meta::console {

enum Code {
    NOP,
    SET,
    GET,
    SHOW,
    REPEAT,
    PAUSE,
//        play,
//        step,
//        clear,
//        push,
//        pop,
};

std::ostream & operator<<(std::ostream & os, const Code & c);

}

#endif /* console_code_hpp */
