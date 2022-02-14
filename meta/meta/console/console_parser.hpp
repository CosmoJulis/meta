//
//  console_parser.hpp
//  meta
//
//  Created by Cosmo Julis on 2/9/22.
//

#ifndef console_parser_hpp
#define console_parser_hpp

#include <iostream>

namespace meta::console {








class Parser {
public:
    
    static Parser & shared();
    static void clear();
    
    // TODO: tokenizer (\", space)
    
    enum Token {
        DOUDLBE_QUOTATION,
        SPACE,
    };
    
    void parser(const std::stringstream & ss) {
    
    }
    
    void parser(const std::string & str) {
        // TODO: parse str
//        "set get 0 index name \"hello world\"";
//        "set 0 age false";
//        "set 0 repeat 10";
//        "set 0 sleep true";
//        "set 0 set set";
//        "set 0 name hello";
//        "set 0 name \"hello world\"";
//        "set 0 age 12";
//        "set 0 name \"123\"";
    }
    
};

}

#endif /* console_parser_hpp */
