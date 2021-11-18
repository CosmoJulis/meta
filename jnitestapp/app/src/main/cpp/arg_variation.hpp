//
//  arg_modifer.hpp
//  meta
//
//  Created by Cosmo Julis on 11/15/21.
//

#ifndef arg_modifer_hpp
#define arg_modifer_hpp


#include <type_traits>


namespace meta {

namespace arg {



// TODO: static_assert for args...
/*
 * add_const variadic template
 */
//template <typename T>
//struct remove_const_reference {
//    using type = std::remove_const_t<std::remove_reference_t<T>>;
//};
//
//template <typename T>
//using remove_const_reference_t = typename remove_const_reference<T>::type;
//
//template <typename T>
//using remove_reference_const_t = typename remove_const_reference<T>::type;



//template <typename T, typename ... Args>
//struct remove_const {
//
//    template <typename _T, typename ... _Args>
//    struct _impl {
//        using _type = typename _impl<std::remove_const_t<_T>, _Args...>::_type;
//    };
//
//    template <typename _T>
//    struct _impl<_T> {
//        using _type = std::remove_const_t<_T>;
//    };
//
//    using type = typename _impl<T, Args...>::_type;
//};


//template <typename T, typename ... Args>
//struct add_const {
//
//    template <typename _T, typename ... _Args>
//    struct _impl {
//        using _type = typename _impl<std::add_const_t<_T>, _Args...>::_type;
//    };
//
//    template <typename _T>
//    struct _impl<_T> {
//        using _type = std::add_const_t<_T>;
//    };
//
//    using type = typename _impl<T, Args...>::_type;
//};






}

}

#endif /* arg_modifer_hpp */
