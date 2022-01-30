//
//  console_manager.hpp
//  meta
//
//  Created by Cosmo Julis on 1/30/22.
//

#ifndef console_manager_hpp
#define console_manager_hpp

#include <stack>
#include <queue>
#include "arg.hpp"
#include "console_instruction.hpp"

namespace meta::console {

class Manager {
public:
    
    static Manager & shared() {
        static Manager * pm = new Manager();
        return *pm;
    }
    
    template <typename T>
    void push(const T & t) {
        if constexpr (std::is_same_v<T, Code>) {
            add(Instruction(t));
        }
        else if constexpr (NumberSupportType<T>) {
            top().push(Number(t));
        }
        else if constexpr (std::is_same_v<T, std::string>) {
            top().push(t);
        }
        else {
            throw "Type not match.";
        }
        popFullInstruction();
    }
    
    void execute() {
        while (_queue.size() > 0) {
            
        }
    }

private:
    
    void popFullInstruction() {
        auto pi = _stack.top();
        if (pi->isBranchFull()) {
            _stack.pop();
        }
    }
    
    Instruction & top() const {
        if (_stack.size() > 0) {
            return *(_stack.top());
        } else {
            throw "Missing instruction.";
        }
    }
    
    void add(const Instruction & inst) {
        auto pi = new Instruction(inst);
        _stack.push(pi);
        _queue.push(pi);
    }
    
    std::stack<Instruction *> _stack;
    std::queue<Instruction *> _queue;
    
    
//    void perform(Statement & s);
    
};

}

#endif /* console_manager_hpp */
