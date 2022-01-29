//
//  console_queue.hpp
//  meta
//
//  Created by Cosmo Julis on 1/29/22.
//

#ifndef console_queue_hpp
#define console_queue_hpp

#include <queue>
#include "console_stack.hpp"

namespace meta::console {

class Queue {
public:
    
    void push(const Stack & s) {
        _stack_queue.push(s);
    }
    
    Stack & front() {
        return _stack_queue.front();
    }
    
    void pop() {
        _stack_queue.pop();
    }

    size_t size() const {
        return _stack_queue.size();
    }
    
private:
    std::queue<Stack> _stack_queue;
};

}

#endif /* console_queue_hpp */
