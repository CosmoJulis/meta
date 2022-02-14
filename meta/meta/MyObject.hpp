//
//  MyObject.hpp
//  meta
//
//  Created by Cosmo Julis on 1/29/22.
//

#ifndef MyObject_hpp
#define MyObject_hpp

#include "console/console.hpp"

namespace meta::console {

class MyObject : public Object {
public:
    
    MyObject(int id = 0) : Object(id) {
        Pool::shared().obj_id_map[id] = std::shared_ptr<MyObject>(new MyObject(*this));
    }
    
    int age = 0;
    float height = 0;
    std::string name = "";

    void set(const std::string & key, const Reg & value) override {
        if (key == "age") {
            age = value.get_number();
            std::cout << "set age " << age << std::endl;
        }
        else if (key == "height") {
            height = value.get_number();
        }
        else if (key == "name") {
            name = value.get_string();
        }
    }
    
    Reg get(const std::string & key) override {
        if (key == "age") {
            return Reg(Number(age));
        }
        else if (key == "height") {
            return Reg(Number(height));
        }
        else if (key == "name") {
            return Reg(name);
        }
        return Reg();
    }
    
    void log() override {
        std::cout << "MyObject\n";
    }
};

}



#endif /* MyObject_hpp */
