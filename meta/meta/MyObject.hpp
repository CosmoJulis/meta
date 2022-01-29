//
//  MyObject.hpp
//  meta
//
//  Created by Cosmo Julis on 1/29/22.
//

#ifndef MyObject_hpp
#define MyObject_hpp

#include "console.hpp"

class MyObject : public meta::console::Object {
public:
    int age;
    float height;
    int name;
    void set_age(int age) {
        std::cout << "set_age(" << age << ")" << std::endl;
    }
    void set_height(float height) {
        std::cout << "set_height(F" << height << ")" << std::endl;
    }
    void set_name(std::string name) {
        std::cout << "set_name(" << name << ")" << std::endl;
    }
};

#endif /* MyObject_hpp */
