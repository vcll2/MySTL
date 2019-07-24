#ifndef __MYSTL_CONSTRUCT_H
#define __MYSTL_CONSTRUCT_H

#include<new>
#include"type_traits.h"

namespace mystl {

template<class T1, class T2>
inline void construct(T1 *p, const T2& value) {
    new (p) T1(value);
}

template<class T>
inline void destroy(T *ptr) {
    ptr->~T();
}

template<class ForwardIterator>
inline void destroy(ForwardIterator first, ForwardIterator last) {
    typedef typename _type_traits<ForwardIterator>::is_POD_type is_POD_type;
    _destroy(first, last, is_POD_type());
}

template<class ForwardIterator>
inline void _destroy(ForwardIterator first, ForwardIterator last, _true_type) {}

template<class ForwardIterator>
inline void _destroy(ForwardIterator first, ForwardIterator last, _false_type) {
    for(; first != last; ++first) {
        destroy(&*first);
    }
}

}

#endif
