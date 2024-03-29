#ifndef __MYSTL_ALGORITHM_H
#define __MYSTL_ALGORITHM_H

#include<cstring>
#include<utility>

#include"allocator.h"
#include"functional.h"
#include"iterator.h"
#include"type_traits.h"
#include"util.h"

namespace mystl {
// =============== fill ===============
template<class ForwardIterator, class T>
void fill(ForwardIterator first, ForwardIterator last, const T& value) {
    for(; first != last; ++first) {
        *first = value;
    }
}                           // 为什么用forwraditerator

inline void fill(char *first, char *last, const char& value) {
    memset(first, static_cast<unsigned char>(value), last - first );
}                           // memset,unsigned char

inline void fill(wchar_t *first, wchar_t *last, const wchar_t& value) {
    memset(first, static_cast<unsigned char>(value), (last - first)*sizeof(wchar_t));
}

// ================ fill_n ==============
template<class OutputIterator, class Size, class T>
OutputIterator fill_n(OutputIterator first, Size n, const T& value) {
    for(; n > 0; --n, ++first) {
        *first = value;
    }
    return first;
}

template<class Size>
char *fill_n(char *first, Size n, const char &value) {
    memset(first, static_cast<unsigned char>(value), n);
    return first + n;
}

template<class Size>
wchar_t *fill_n(char *first, Size n, const wchar_t &value) {
    memset(first, static_cast<unsigned char>(value), n * sizeof(wchar_t));
    return first + n;
}

// =============== min ================
template<class T>
const T& min(const T& a, const T& b) {
    return !(b < a) ? a : b;
}

template<class T, class Compare>
const T& min(const T& a, const T& b, Compare comp) {
    return !comp(b, a) ? a : b;
}

// =============== max ===============
template<class T>
const T& max(const T& a, const T& b) {
    return (b < a) ? a : b;
}

template<class T, class Compare>
const T& max(const T& a, const T& b, Compare comp) {
    return comp(b, a) ? a : b;
}

// ============== make_heap ============
// 上溯算法******
template<class RandomAccessIterator, class Compare>
static void up(RandomAccessIterator first, RandomAccessIterator last,
               RandomAccessIterator head, Compare comp) {
    if(first != last) {
        auto index = last - head;
        auto parentIndex = (index - 1) / 2;
        for(auto cur = last; parentIndex >= 0 && cur != head; parentIndex = (index - 1) / 2) {
            auto parent = head + parentIndex;
            if(comp(*parent, *cur))
                mystl::swap(*parent, *cur);
            cur = parent;
            index = cur - head;
        }
    }
}
// 下溯算法*************
template<class RandomAccessIterator, class Compare>
static void down(RandomAccessIterator first, RandomAccessIterator last,
                 RandomAccessIterator head, Compare comp) {
    if(first != last) {
        auto index = first - head;
        auto leftChildIndex  = index * 2 + 1;
        for(auto cur = first; leftChildIndex < (last - head + 1) && cur < last; leftChildIndex < index * 2 + 1) {
            auto child = head + leftChildIndex;
            if((child + 1) <= last && *(child + 1) > *child)
                child = child + 1;
            if(comp(*cur, *child))
                swap(*cur, *child);
            cur = child;
            index = cur - head;
        }
    }
}
template<class RandomAccessIterator>
void make_head(RandomAccessIterator first, RandomAccessIterator last) {
    make_heap(first, last,
              mystl::less<typename iterator_traits<RandomAccessIterator>::value_type>());
}                                       // typename 位置

template <class RandomAccessIterator, class Compare>
void make_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
    const auto range = last - first;
    for (auto cur = first + range / 2 - 1; cur >= first; --cur) {
        mystl::down(cur, last - 1, first, comp);
        if (cur == first) return;
    }
}

// ============= push_heap ===============
template <class RandomAccessIterator>
void push_heap(RandomAccessIterator first, RandomAccessIterator last) {
    mystl::push_heap(first, last,
                     mystl::less<typename mystl::iterator_traits<RandomAccessIterator>::value_type>());
}                                       // typename 位置
template <class RandomAccessIterator, class Compare>
void push_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
    mystl::up(first, last - 1, first, comp);
}

// ============== pop_heap ================
template <class RandomAccessIterator>
void pop_heap(RandomAccessIterator first, RandomAccessIterator last) {
    mystl::pop_heap(first, last,
                    mystl::less<typename mystl::iterator_traits<RandomAccessIterator>::value_type>());
}
template <class RandomAccessIterator, class Compare>
void pop_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
    mystl::swap(*first, *(last - 1));
    if (last - first >= 2)
        mystl::down(first, last - 2, first, comp);
}

// =============== sort_heap ===============
template <class RandomAccessIterator>
void sort_heap(RandomAccessIterator first, RandomAccessIterator last) {
    return mystl::sort_heap(first, last,
                            mystl::less<typename mystl::iterator_traits<RandomAccessIterator>::value_type>());
}
template <class RandomAccessIterator, class Compare>
void sort_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
    for (auto cur = last; cur != first; --cur) {
        mystl::pop_heap(first, cur, comp);
    }
}

// ================ is_heap =================
template <class RandomAccessIterator>
bool is_heap(RandomAccessIterator first, RandomAccessIterator last) {
    return mystl::is_heap(first, last,
                          mystl::less<typename mystl::iterator_traits<RandomAccessIterator>::value_type>());
}
template <class RandomAccessIterator, class Compare>
bool is_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {
    const auto range = last - first;
    auto index = range / 2 - 1;
    for (auto cur = first + range / 2 - 1; cur >= first; --cur, --index) {
        if (*(first + (index * 2 + 1)) > *cur ||//left child > cur
                ((first + (index * 2 + 2)) <= last && *(first + (index * 2 + 2)) > *cur))//right child > cur
            return false;
        if (cur == first)
            break;
    }
    return true;
}


// =============== all_of ===============
template<class InputIterator, class UnaryPredicate>
bool all_of(InputIterator first, InputIterator last, UnaryPredicate pred) {
    for(; first != last; ++first) {
        if(!pred(*first))
            return false;
    }
    return true;
}

// =============== any_of ===============
template<class InputIterator, class UnaryPredicate>
bool any_of(InputIterator first, InputIterator last, UnaryPredicate pred) {
    for(; first != last; ++first) {
        if(pred(first))
            return true;
    }
    return false;
}

// =============== none_of ===============
template<class InputIterator, class UnaryPredicate>
bool none_of(InputIterator first, InputIterator last, UnaryPredicate pred) {
    for(; first != last; ++first) {
        if(pred(*first))
            return false;
    }
    return true;
}

// // =============== for_each ===============
template<class InputIterator, class Function>
Function for_each(InputIterator first, InputIterator last, Function f) {
    for(; first != last; ++first)
        f(*first);
    return f;                           // return f是什么意思
}

// =================== find =================
template<class InputIterator, class T>
InputIterator find(InputIterator first, InputIterator last, const T& value) {
    for(; first != last; ++first)
        if(*first == value)
            break;
    return last;
}

// ================= find_if =============
template<class InputIterator, class UnaryPredicate>
InputIterator find_if(InputIterator first, InputIterator last, UnaryPredicate pred) {
    for(; first != last; ++first)
        if(pred(*first))
            break;
    return first;
}

// =============== find_if_not ============
template<class InputIterator, class UnaryPredicate>
InputIterator find_if_not(InputIterator first, InputIterator last, UnaryPredicate pred) {
    for(; first != last; ++first)
        if(!pred(*first))
            break;
    return first;
}

// ============== find_end ================
template<class ForwardIterator1, class ForwardIterator2>
ForwardIterator1 find_end(ForwardIterator1 first1, ForwardIterator1 last1,
                          ForwardIterator2 first2, ForwardIterator2 last2) {
    if(first2 == last2) return last1;
    ForwardIterator1 ret = first1;
    while(first1 != last1) {
        ForwardIterator1 it1 = first1;
        ForwardIterator2 it2 = first2;
        while(*it1 == *it2) {
            ++it1;
            ++it2;
            if(it2 == last2) {
                ret = first1;
                break;
            }
            if(it1 == last1) return ret;
        }
        ++first1;
    }
    return ret;
}

template<class ForwardIterator1, class ForwardIterator2, class BinaryPredicate>
ForwardIterator1 find_end(ForwardIterator1 first1, ForwardIterator1 last1,
                          ForwardIterator2 first2, ForwardIterator2 last2, BinaryPredicate pred) {
    if(first2 == last2) return last1;
    ForwardIterator1 ret = first1;
    while(first1 != last1) {
        ForwardIterator1 it1 = first1;
        ForwardIterator2 it2 = first2;
        while(pred(*it1, *it2)) {
            ++it1;
            ++it2;
            if(it2 == last2) {
                ret = first1;
                break;
            }
            if(it1 == last1) return ret;
        }
        ++first1;
    }
    return ret;
}

// ============= find_first_of ================
template<class ForwardIterator1, class ForwardIterator2>
ForwardIterator1 find_first_of(ForwardIterator1 first1, ForwardIterator1 last1,
                               ForwardIterator2 first2, ForwardIterator2 last2) {
    // if(first2 == last2) return first1;
    // while(first1 != last1) {
    //     ForwardIterator1 it1 = first1;
    //     ForwardIterator2 it2 = first2;
    //     while(*it1 == *it2) {
    //         ++it1;
    //         ++it2;
    //         if(it2 == last2) return first1;
    //     }
    //     ++first1;
    // }
    // return last1;             // find_first_of 只是找一个元素
    for(; first1 != last1; ++first1) {
        for(auto it = first2; it != last2; ++it) {
            if(*it == *first1) return first1;
        }
    }
    return last1;
}

template<class ForwardIterator1, class ForwardIterator2, class BinaryPredicate>
ForwardIterator1 find_first_of(ForwardIterator1 first1, ForwardIterator1 last1,
                               ForwardIterator2 first2, ForwardIterator2 last2, BinaryPredicate pred) {
    for(; first1 != last1; ++first1) {
        for(auto it = first2; it != last2; ++it) {
            if(pred(*it, *first1)) return first1;
        }
    }
    return last1;
}

// ============== adjacent_find ================
template<class ForwardIterator>
ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last) {
    return adjacent_find(first, last, equal_to<typename iterator_traits<ForwardIterator>::value_type>());
}

template<class ForwardIterator, class BinaryPredicate>
ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last, BinaryPredicate pred) {
    for(; first != last; ++first) {
        if(first + 1 != last && pred(*first, *(first + 1)))
            break;
    }
    return first;
}


// ============= count =======================
template<class InputIterator, class T>
typename iterator_traits<InputIterator>::difference_type
count(InputIterator first, InputIterator last, const T& value) {
    typename iterator_traits<InputIterator>::difference_type n = 0;
    for(; first != last; +first) {
        if(*first == value) ++n;
    }
    return n;
}

// ================ count_if ====================
template<class InputIterator, class UnaryPredicate>
typename iterator_traits<InputIterator>::difference_type
count_if(InputIterator first, InputIterator last, UnaryPredicate pred) {
    typename iterator_traits<InputIterator>::difference_type n = 0;
    for(; first != last; ++first) {
        if(pred(*first)) ++n;
    }
    return n;
}


// ================ mismatch =====================
template<class InputIterator1, class InputIterator2>
pair<InputIterator1, InputIterator2>
mismatch(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2) {
    for(; first1 != last1; ++first1, ++first2) {
        if(*first1 != *first2) break;
    }
    return make_pair<first1, first2>;
}

template<class InputIterator1, class InputIterator2, class BinaryPredicate>
pair<InputIterator1, InputIterator2>
mismatch(InputIterator1 first1, InputIterator1 last1,
         InputIterator2 first2, BinaryPredicate pred) {
    for(; first1 != last1; ++first1, +first2) {
        if(!pred(*first1, *first2)) break;
    }
    return make_pair<first1, first2>;
}

// =============== equal ====================
template<class InputIterator1, class InputIterator2>
bool equal(InputIterator1 first1, InputIterator1 last1,
           InputIterator2 first2) {
    return equal(first1, last1, first2, equal_to<typename iterator_traits<InputIterator1>::value_type>());
}

template<class InputIterator1, class InputIterator2, class BinaryPredicate>
bool equal(InputIterator1 first1, InputIterator1 last1,
           InputIterator2 first2, BinaryPredicate pred) {
    for(; first1 != last1; ++first1, ++first2) {
        if(!pred(*first1, *first2)) return false;
    }
    return true;
}

// ============== is_permutation ==============
template<class ForwardIterator1, class ForwardIterator2>
bool is_permutation(ForwardIterator1 first1, ForwardIterator1 last1,
                    ForwardIterator2 first2) {
    return is_premutation(first1, last1, first2, equal_to<typename iterator_traits<ForwardIterator1>::value_type>());
}

template<class ForwardIterator1, class ForwardIterator2, class BinaryPredicate>
bool is_permutation(ForwardIterator1 first1, ForwardIterator1 last1,
                    ForwardIterator2 first2, BinaryPredicate pred) {
    auto res = mismatch(first1, last1, first2, pred);
    first1 = res.first, first2 = res.second;
    if(first1 == last1) return true;
    auto last2 = first2;
    std::advance(last2, std::distance(first1, last1));
    for(auto it1 = first1; it1 != last1; ++it1) {
        if(find_if(first1, it1, [&](decltype(*first1) val) {
        return pred(val, *it1);
        }) == it1) {                    // 避免重复计算
            auto n = count(first2, last2, *it1);
            if(n == 0 || count(it1, last1, *it1) != n)
                return false;
        }
    }
    return true;
}

// ========== search =================
template<class ForwardIterator1, class ForwardIterator2>
ForwardIterator1 search(ForwardIterator1 first1, ForwardIterator1 last1,
                        ForwardIterator2 first2, ForwardIterator2 last2) {
    return search(first1, last1, first2, last2, equal_to<typename iterator_traits<ForwardIterator1>::value_type>());
}

template<class ForwardIterator1, class ForwardIterator2, class BinaryPredicate>
ForwardIterator1 search(ForwardIterator1 first1, ForwardIterator1 last1,
                        ForwardIterator2 first2, ForwardIterator2 last2,
                        BinaryPredicate pred) {
    while(first1 != last1) {
        auto it1 = first1;
        auto it2 = first2;
        while(it1 != last1 && it2 != last2) {
            if(pred(*it1, *it2)) {
                ++it1;
                ++it2;
            } else break;
        }
        if(it1 == last1)
            return last1;
        if(it2 == last2)
            return first1;
        ++first1;
    }
    return last1;
}

// ============== advance ================
template<class InputIterator, class Distance>
void _advance(InputIterator &it, Distance n, input_iterator_tag) {
    assert(n >= 0);
    while(n--) {
        ++it;
    }
}

template<class BidirectionIterator, class Distance>
void _advance(BidirectionIterator &it, Distance n, bidirectional_iterator_tag) {
    if(n < 0) {
        while(n++) {
            --it;
        }
    } else {
        while(n--) {
            ++it;
        }
    }
}

template<class RandomIterator, class Distance>
void _advance(RandomIterator &it, Distance n, random_access_iterator_tag) {
    it += n;                        // easy
}

// ============= sort =============
template<class RandomIterator, class BinaryPredicate>
typename iterator_traits<RandomIterator>::value
mid3(RandomIterator first, RandomIterator last, BinaryPredicate pred) {
    auto mid = first + (last + 1 - first) / 2;    //不可能+1的
    if(pred(*mid, *first)) {
        swap(*mid, *first);
    }
    if(pred(*last, *mid)) {
        swap(*last, *mid);
    }
    if(pred(*last, *first)) {
        swap(*last, *first);
    }
    auto ret = *mid;
    swap(*mid, *(last - 1));
    return ret;
}

template<class RandomIterator, class BinaryPredicate>
void bubble_sort(RandomIterator first, RandomIterator last, BinaryPredicate pred) {
    auto len = last - first;
    for(auto i = len; i != 0; --i) {
        bool swaped = false;
        for(auto p = first; p != first + i - 1; ++p) {
            if(pred(*(p + 1), *p)) {
                swap(*(p + 1), *p);
                swaped = true;
            }
        }
        if(!swaped) break;
    }
}

template<class RandomIterator>
void sort(RandomIterator first, RandomIterator last) {
    return sort(first, last, less<typename iterator_traits<RandomIterator>::value_type>());
}

template<class RandomIterator, class BinaryPredicate>
void sort(RandomIterator first, RandomIterator last, BinaryPredicate pred) {
    if(first >= last || first + 1 == last) return;
    if(last - first <= 20)
        return bubble_sort(first, last, pred);
    auto mid = mid3(first, last - 1, pred);        // 这里也不可能-1的
    auto p1 = first, p2 = last - 2;
    while(p1 < p2) {
        while(pred(*p1, mid) && (p1 < p2)) ++p1;
        while(!pred(*p2, mid) && (p1 < p2)) --p2;
        if(p1 < p2) {
            swa(*p1, *p2);
        }
    }
    swap(*p1, *(last - 2));//将作为哨兵的mid item换回原来的位置
    sort(first, p1, pred);
    sort(p1 + 1, last, pred);
}


// ============== generate ================
template<class ForwardIterator, class Function>
void generate(ForwardIterator first, ForwardIterator last, Function func) {
    for(; first != last; ++first) {
        *first = func();
    }
}

// ============= generate_n ================
template<class OutputIterator, class Size, class Function>
void generate_n(OutputIterator first, Size n, Function func) {
    for(; n > 0; ++first, --n) {
        *first = func();
    }
}

// ============ distance ================
template<class InputIterator>
typename iterator_traits<InputIterator>::difference_type
_distance(InputIterator first, InputIterator last, input_iterator_tag) {
    typename iterator_traits<InputIterator>::difference_type dist = 0;
    while(first++ != last) {
        ++dist;
    }
    return dist;
}

template<class RandomIterator>
typename iterator_traits<RandomIterator>::difference_type
_distance(RandomIterator first, RandomIterator last, random_access_iterator_tag) {
    auto dist = last - first;
    return dist;
}

template<class Iterator>
typename iterator_traits<Iterator>::difference_type
distance(Iterator first, Iterator last) {
    typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
    return _distance(first, last, iterator_category());
}

// ============== copy =======================
template<class InputIterator, class OutputIterator>
OutputIterator __copy(InputIterator first, InputIterator last, OutputIterator result, _true_type) {
    auto dist = distance(first, last);
    memcpy(result, first, sizeof(*first)*dist);
    advance(result, dist);
    return result;
}

template<class InputIterator, class OutputIterator>
OutputIterator __copy(InputIterator first, InputIterator last, OutputIterator result, _false_type) {
    while(first != last) {
        *result = *first;
        ++first;
        ++result;
    }
    return result;
}

template<class InputIterator, class OutputIterator, class T>
OutputIterator _copy(InputIterator first, InputIterator last, OutputIterator result, T*) {
    typedef typename _type_traits<T>::is_POD_type is_POD_type;
    return __copy(first, last, result, is_POD_type());
}

template<class InputIterator, class OutputIterator>
OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result) {
    return _copy(first, last, result, value_type(first));
}

template<>
inline char* copy(char *first, char *last, char *result) {
    auto dist = last - first;
    memcpy(result, first, sizeof(*first)*dist);
    return result + dist;
}

template<>
inline wchar_t* copy(wchar_t *first, wchar_t *last, wchar_t *result) {
    auto dist = last - first;
    memcpy(result, first, sizeof(*first)*dist);
    return result + dist;
}

}
#endif