//
//  string_utility.hpp
//  meta
//
//  Created by Cosmo Julis on 11/12/21.
//

#ifndef string_utility_hpp
#define string_utility_hpp

#include <vector>
#include <string>


namespace meta::string {

    static inline const std::vector<std::string> split(const std::string & s, const std::string & split)
    {
        std::vector<std::string> sv;
        size_t start = 0;
        size_t end = s.find(split);
        while (end != -1) {
            sv.push_back(s.substr(start, end - start));
            start = end + split.size();
            end = s.find(split, start);
        }
        sv.push_back(s.substr(start, end - start));
        return sv;
    }

    static inline const std::string join(const std::vector<std::string> & sv, const std::string & join = "")
    {
        std::string ret;
        for (auto p = sv.begin(); p != sv.end(); p++) {
            ret += *p;
            if (p+1 != sv.end()) {
                ret += join;
            }
        }
        return ret;
    }

}

#endif /* string_utility_hpp */
