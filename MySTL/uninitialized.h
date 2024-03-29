#ifndef __MYSTL_UNINITIALIZED_H
#define __MYSTL_UNINITIALIZED_H

#include"algorithm.h"
#include"construct.h"
#include"iterator.h"
#include"type_traits.h"

namespace mystl {

// ================== copy ========================
template<class InputIterator, class ForwardIterator>
ForwardIterator _uninitialized_copy_aux(InputIterator first, InputIterator last,
                                        ForwardIterator result, _true_type);

template<class InputIterator, class ForwardIterator>
ForwardIterator _uninitialized_copy_aux(InputIterator first, InputIterator last,
                                        ForwardIterator result, _false_type);

template<class InputIterator, class ForwardIterator>
ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result) {
    typedef typename _type_traits<typename iterator_traits<InputIterator>::value_type>::is_POD_type is_POD_type;
    return _uninitialized_copy_aux(first, last, result, is_POD_type());     // 双typename
}

template<class InputIterator, class ForwardIterator>
ForwardIterator _uninitialized_copy_aux(InputIterator first, InputIterator last,
                                        ForwardIterator result, _true_type) {
    memcpy(result, first, (last - first)*sizeof(*first));
    return result + (last - first);     // 为什么返回最后位置
}

template<class InputIterator, class ForwardIterator>
ForwardIterator _uninitialized_copy_aux(InputIterator first, InputIterator last,
                                        ForwardIterator result, _false_type) {
    ForwardIterator cur = result;
    for(; first != last; ++first, ++cur) {
        construct(&*cur, *first);
    }
    return cur;
}                                       // changed


// ================== fill ========================
template<class ForwardIterator, class T>
void _uninitialized_fill_aux(ForwardIterator first, ForwardIterator last,
                             const T& value, _true_type);

template<class ForwardIterator, class T>
void _uninitialized_fill_aux(ForwardIterator first, ForwardIterator last,
                             const T& value, _false_type);

template<class ForwardIterator, class T>
void uninitialized_fill(ForwardIterator first, ForwardIterator last,
                        const T& value) {
    typedef typename _type_traits<T>::is_POD_type is_POD_type;
    return _uninitialized_fill_aux(first, last, value, is_POD_type());
}

template<class ForwardIterator, class T>
void _uninitialized_fill_aux(ForwardIterator first, ForwardIterator last,
                             const T& value, _true_type) {
    fill(first, last, value);
}

template<class ForwardIterator, class T>
void _uninitialized_fill_aux(ForwardIterator first, ForwardIterator last,
                             const T& value, _false_type) {
    for(; first != last; ++first) {
        construct(&*first, value);
    }
}

// ================== fill_n ========================
template<class ForwardIterator, class Size, class T>
ForwardIterator _uninitialized_fill_n_aux(ForwardIterator first,
        Size n, const T& x, _true_type);

template<class ForwardIterator, class Size, class T>
ForwardIterator _uninitialized_fill_n_aux(ForwardIterator first,
        Size n, const T& x, _false_type);

template<class ForwardIterator, class Size, class T>
inline ForwardIterator uninitialized_fill_n(ForwardIterator first,
        Size n, const T& x) {
    typedef typename _type_traits<T>::is_POD_type is_POD_type;
    return _uninitialized_fill_n_aux(first, n, x, is_POD_type());
}

template<class ForwardIterator, class Size, class T>
ForwardIterator _uninitialized_fill_n_aux(ForwardIterator first,
        Size n, const T& x, _true_type) {
    return fill_n(first, n, x);
}

template<class ForwardIterator, class Size, class T>
ForwardIterator _uninitialized_fill_n_aux(ForwardIterator first,
        Size n, const T& x, _false_type) {
    ForwardIterator cur = first;
    for(; n > 0; --n, ++cur) {
        construct(&*cur, x);
    }
    return cur;
}

}

#endif
