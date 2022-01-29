//
//  console_manager.hpp
//  meta
//
//  Created by Cosmo Julis on 1/29/22.
//

#ifndef console_manager_hpp
#define console_manager_hpp

#include "console_queue.hpp"
#include "console_run.hpp"

namespace meta::console {

class Manager {
public:
    
    static Manager & shared() {
        static Manager * pm = new Manager();
        return *pm;
    }
    
    void push(const Stack & stack) {
        _queue.push(stack);
    }
    
    void pop() {
        _queue.pop();
    }
    
    Stack & currentStack() {
        return _queue.front();
    }
    
    size_t size() const {
        return _queue.size();
    }
    
    void execute() {
        while (size() > 0) {
            run(currentStack());
            pop();
        }
    }

private:
    
    Queue _queue;
    

    
};

}

#endif /* console_manager_hpp */
