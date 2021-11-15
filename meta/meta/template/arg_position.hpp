//
//  arg_position.hpp
//  meta
//
//  Created by Cosmo Julis on 11/11/21.
//

#ifndef arg_position_hpp
#define arg_position_hpp

/*
 * TODO: ignore const
 *       ignore reference
 *       ignore const | reference
 */

namespace meta {

namespace arg {


/*
 *  Get first index T at Args...
 *  -1 no exist
 *  获取 T 在 Args... 中的第一个位置
 *  -1 不存在
 */
template<typename T, typename... Args>
struct index_of {
    
    template<typename _T, int _index, typename _F, typename ... _Args>
    struct _impl {
        static constexpr int getIndex() {
            if constexpr (std::is_same_v<_T, _F>) {
                return _index + 1;
            } else {
                return _impl<_T, _index + 1, _Args...>::getIndex();
            }
        }
    };

    template<typename _T, int _index, typename _F>
    struct _impl<_T, _index, _F> {
        static constexpr int getIndex() {
            if constexpr (std::is_same_v<_T, _F>) {
                return _index + 1;
            } else {
                return -1;
            }
        }
    };

    template<typename _T, int _idx, typename _F, typename _J>
    struct _impl<_T, _idx, _F, _J> {
        static constexpr int getIndex() {
            if constexpr (std::is_same_v<_T, _F>) {
                return _idx + 1;
            } else {
                return _impl<_T, _idx + 1, _J>::getIndex();
            }
        }
    };
    
    
    struct _placeholder { };
    
    using ArgsType = std::conditional_t
                            <
                                sizeof...(Args) == 0,
                                _impl<T, -2, _placeholder>,
                                _impl<T, -2, _placeholder, Args...>
                            >;
    
    static inline constexpr int index = ArgsType::getIndex();
};



/*
 *  Get arg at position in args
 *  throw not found
 *  根据index获取Args的类型
 *  找不到会抛出异常
 *  index must constexpr
 */
//template<size_t index, typename... Args>
//struct at {
//    using type = int;
//    // TODO:
//};




}

}

#endif /* arg_position_hpp */
