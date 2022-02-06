//
//  console_manager.hpp
//  meta
//
//  Created by Cosmo Julis on 1/30/22.
//

#ifndef console_manager_hpp
#define console_manager_hpp

#include <map>
#include <stack>
#include <queue>
#include "arg.hpp"
#include "console_instruction.hpp"

namespace meta::console {

class Manager {
public:
    
    static Manager & shared();
    static void clear();
    
    template <typename T>
    void push(const T t) {
        if constexpr (std::is_same_v<T, Code>) {
            int inst_id = map_add(Instruction(t));
            if (stack_size() > 0) {
                stack_top().push(inst_id);
            } else {
                _inst_queue.push(inst_id);
            }
            stack_push(inst_id);
        }
        else if constexpr (NumberSupportType<T>) {
            stack_top().push(Number(t));
        }
        else if constexpr (std::is_same_v<T, std::string> || std::is_same_v<T, const char *>) {
            stack_top().push(std::string(t));
        }
        else {
            std::cout << meta::arg::list_log<T> << std::endl;
            throw "Type not match.";
        }
        popFullInstruction();
    }
    

    
    void popFullInstruction() {
//        while (_inst_stack.size() > 0) {
//            if (_map.contains(_inst_stack.top())) {
//                auto & i = _map[_inst_stack.top()];
//                if (i.isFullBranch()) {
//                    _inst_stack.pop();
//                    continue;
//                }
//            }
//            break;
//        }
    }
    
    void execute() {
//        std::cout << "queue size: " << _queue.size() << std::endl;
//        std::cout << "stack size: " << _inst_stack.size() << std::endl;
//        while (_queue.size() > 0) {
//            std::cout << "queue pop\n";
//            _queue.pop();
//        }
//        _map.clear();
    }

private:
    
    int _icount = 0;
    std::map<int, Instruction> _inst_map;
    
    int map_add(const Instruction & inst) {
        int r = _icount;
        _inst_map[_icount] = inst;
        _icount++;
        return r;
    }
    
    bool map_remove(int id) {
        if (_inst_map.contains(id)) {
            _inst_map.erase(id);
            return true;
        }
        return false;
    }
    
    Instruction & get(int id) {
        if (_inst_map.contains(id)) {
            return _inst_map[id];
        } else {
            std::string msg = "Missing instruction id: " + std::to_string(id);
            throw msg;
        }
    }
    

    
    
    
    std::stack<int> _inst_stack;
    
    size_t stack_size() const {
        return _inst_stack.size();
    }
    
    void stack_push(const int & id) {
        _inst_stack.push(id);
    }
    
    Instruction & stack_top() {
        if (_inst_stack.size() > 0) {
            return get(_inst_stack.top());
        } else {
            throw "Missing instruction.";
        }
    }
    

    
    std::queue<int> _inst_queue;
    
    void queue_push(const int & id) {
        _inst_queue.push(id);
    }
    
    const int & queue_front() const {
        return _inst_queue.front();
    }
    
    void queue_pop() {
        auto & id = queue_front();
        if (_inst_map.contains(id)) {
            auto & inst = _inst_map[id];
            inst.pop();
            map_remove(id);
        } else {
            throw "Pop instruction index not exist.";
        }
        _inst_queue.pop();
    }

//    void perform(Statement & s);
    
};

}

#endif /* console_manager_hpp */
