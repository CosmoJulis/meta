//
//  console_manager.hpp
//  meta
//
//  Created by Cosmo Julis on 1/30/22.
//

#ifndef console_manager_hpp
#define console_manager_hpp

#include <queue>
#include "console_statement.hpp"

namespace meta::console {

class Manager {
public:
    
    static Manager & shared() {
        static Manager * pm = new Manager();
        return *pm;
    }
    
    void push(const Statement & st) {
        _queue.push(st);
    }
    
    void pop() {
        _queue.pop();
    }
    
    Statement & currentStatement() {
        return _queue.front();
    }
    
    size_t size() const {
        return _queue.size();
    }
    
    void execute() {
        while (size() > 0) {
            perform(currentStatement());
            pop();
        }
    }

private:
    
    std::queue<Statement> _queue;
    
    void perform(Statement & s);
    
};

}

#endif /* console_manager_hpp */
