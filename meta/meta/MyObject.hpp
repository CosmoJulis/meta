//
//  MyObject.hpp
//  meta
//
//  Created by Cosmo Julis on 1/29/22.
//

#ifndef MyObject_hpp
#define MyObject_hpp

#include "console_object.hpp"

class MyObject : public meta::console::Object {
public:

    MyObject(int id = 0) : meta::console::Object(id) {
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
        Reg r;
        if (key == "age") {
            r.set(Number(age));
        }
        else if (key == "height") {
            r.set(Number(height));
        }
        else if (key == "name") {
            r.set(name);
        }
        return r;
    }
    
    void log() override {
        std::cout << "MyObject\n";
    }
};

#endif /* MyObject_hpp */
