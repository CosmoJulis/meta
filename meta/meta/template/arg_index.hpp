//
//  arg_index.hpp
//  meta
//
//  Created by Cosmo Julis on 11/11/21.
//

#ifndef arg_index_hpp
#define arg_index_hpp

/*
 * TODO: ignore const
 * TODO: ignore reference
 * TODO: ignore const | reference
 */

namespace meta {

namespace arg {

class index_impl_placeholder {
private:
    index_impl_placeholder() { }
};

template<typename T, int index, typename F, typename ... Args>
struct index_impl {
    static constexpr int getIndex() {
        if constexpr (std::is_same_v<T, F>) {
            return index + 1;
        } else {
            return index_impl<T, index + 1, Args...>::getIndex();
        }
    }
};


template<typename T, int index, typename F>
struct index_impl<T, index, F> {
    static constexpr int getIndex() {
        if constexpr (std::is_same_v<T, F>) {
            return index + 1;
        } else {
            return -1; 
        }
    }
};

template<typename T, int idx, typename F, typename J>
struct index_impl<T, idx, F, J> {
    static constexpr int getIndex() {
        if constexpr (std::is_same_v<T, F>) {
            return idx + 1;
        } else {
            return index_impl<T, idx + 1, J>::getIndex();
        }
    }
};

/*
 *  return T of Args... first index
 *  -1 no exist
 *  获取 T 在 Args... 中的第一个位置
 *  -1 不存在
 */
template<typename T, typename... Args>
struct index_of {
    using ArgsType = std::conditional_t
                            <
                                sizeof...(Args) == 0,
                                index_impl<T, -2, index_impl_placeholder>,
                                index_impl<T, -2, index_impl_placeholder, Args...>
                            >;
    static constexpr int index = ArgsType::getIndex();
};



}

}

#endif /* arg_index_hpp */
