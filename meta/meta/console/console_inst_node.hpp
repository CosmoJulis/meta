//
//  console_inst_node.hpp
//  meta
//
//  Created by Cosmo Julis on 2/10/22.
//

#ifndef console_inst_node_hpp
#define console_inst_node_hpp

#include <iostream>
#include "console_reg.hpp"
#include "../template/arg.hpp"

namespace meta::console::instruction {

class Pointer {
    static ID currentID() {
        return 0;
    }
};

class Node {
public:
    
    Node(const Instruction & inst) : _inst(inst) { }

    void add(const Reg & reg) {
    }
    
    Node & current() {
        return *this;
    }
    
private:
    
    ID _id = 0;
    ID _parent_id = 0;
    Instruction _inst = NOP;
    
    std::vector<Reg> _branchs;
    
};

}

/*
 
                    set
 index:int property:string value:int/string/array


 "set get 0 set set get"
 
 set inst
 get inst
 0   value
 set need value not inst
 set need value not inst
 set need value not inst
 

 while (player.age > 10) {
    player.age++
 }
 
 
 
 index(0).property(set) = string(get)
 
 
 
 
 */

#endif /* console_inst_node_hpp */
