#ifndef __MYSTL_REVERSE_ITERATOR_H
#define __MYSTL_REVERSE_ITERATOR_H

#include"iterator.h"

namespace mystl {

template<class Iterator>
class reverse_iterator_t {
public:
    typedef Iterator iterator_type;
    typedef typename iterator_traits<Iterator>::iterator_category  iterator_category;
    typedef typename iterator_traits<Iterator>::value_type value_type;
    typedef typename iterator_traits<Iterator>::difference_type difference_type;
    typedef typename iterator_traits<Iterator>::pointer pointer;
    typedef const pointer const_pointer;
    typedef typename iterator_traits<Iterator>::reference reference;
    typedef const reference const_reference;

private:
    Iterator base_;     // 正向迭代器
    Iterator cur_;      // 逆向迭代器

public:
    reverse_iterator_t(): base_(0), cur_(0) {}  // 0?
    explicit reverse_iterator_t(const iterator_type& it): base_(it) {
        auto temp = it;
        cur_ = --temp;
    }      //怎么指定class

    template<class Iter>
    reverse_iterator_t(const reverse_iterator_t<Iter>& rev_it) {
        base = (iterator_type)rev_it.base();
        auto temp = base_;
        cur_ = --temp;
    }

    iterator_type base() {
        return base_;
    }
    reference operator*() {
        return (*cur_);
    }
    const_reference operator*() const { //const 函数不会修改成员，const对象调用无法调用非const函数
        return (*cur_);
    }
    pointer operator->() {
        return &(operator*());
    }
    reverse_iterator_t& operator++() {
        --base_;
        --cur_;
        return *this;
    }
    reverse_iterator_t& operator++(int) {
        reverse_iterator_t tmp = *this;
        ++(*this);
        return tmp;
    }
    reverse_iterator_t& operator--() {
        ++base_;
        ++cur_;
        return *this;
    }
    reverse_iterator_t& operator--(int) {
        reverse_iterator_t tmp = *this;
        --(*this);
        return tmp;
    }
    reference operator[](difference_type n) {
        return base()[-n - 1];
    }
    reverse_iterator_t operator+(difference_type n) const;
    reverse_iterator_t& operator+=(difference_type n);
    reverse_iterator_t operator-(difference_type n) const;
    reverse_iterator_t& operator-=(difference_type n);
private:
    Iterator advanceNStep(Iterator it, difference_type n, bool right, random_access_iterator_tag) {
        if(right) {
            it += n;
        } else {
            it -= n;
        }
        return it;
    }
    Iterator advanceNStep(Iterator it, difference_type n, bool right, bidirectional_iterator_tag) {
        difference_type i;
        difference_type absN = (n >= 0 ? n : -n);
        if((right && n > 0) || (!right && n < 0)) {
            for(i = 0; i != absN; ++i) {
                it += 1;
            }
        } else if((!right && n > 0) || (right && n < 0)) {
            for(i = 0; i != absN; ++i) {
                it -= 1;
            }
        }
        return it;
    }
// =========== friends ============
public:
    template <class Iter>
    friend bool operator == (const reverse_iterator_t<Iter>& lhs,
                             const reverse_iterator_t<Iter>& rhs);
    template <class Iter>
    friend bool operator != (const reverse_iterator_t<Iter>& lhs,
                             const reverse_iterator_t<Iter>& rhs);
    template <class Iter>
    friend bool operator < (const reverse_iterator_t<Iter>& lhs,
                            const reverse_iterator_t<Iter>& rhs);
    template <class Iter>
    friend bool operator <= (const reverse_iterator_t<Iter>& lhs,
                             const reverse_iterator_t<Iter>& rhs);
    template <class Iter>
    friend bool operator > (const reverse_iterator_t<Iter>& lhs,
                            const reverse_iterator_t<Iter>& rhs);
    template <class Iter>
    friend bool operator >= (const reverse_iterator_t<Iter>& lhs,
                             const reverse_iterator_t<Iter>& rhs);

    template <class Iter>
    friend reverse_iterator_t<Iter> operator+ (
        typename reverse_iterator_t<Iter>::difference_type n,
        const reverse_iterator_t<Iter>& rev_it);
    template <class Iter>
    friend typename reverse_iterator_t<Iter>::difference_type operator- (
        const reverse_iterator_t<Iter>& lhs,
        const reverse_iterator_t<Iter>& rhs);
};

template<class Iterator>
reverse_iterator_t<Iterator>& reverse_iterator_t<Iterator>::operator+=(difference_type n) {
    base_ = advanceNStep(base_, n, false, iterator_category());  // 没参数?
    cur_ = advanceNStep(cur_, n, false, iterator_category());
    return *this;
}

template<class Iterator>
reverse_iterator_t <Iterator>& reverse_iterator_t<Iterator>::operator-=(difference_type n) {
    base_ = advanceNStep(base_, n, true, iterator_category());
    cur_ = advanceNStep(cur_, n, true, iterator_category());
    return *this;
}

template<class Iterator>
reverse_iterator_t<Iterator> reverse_iterator_t<Iterator>::operator + (difference_type n)const {
    reverse_iterator_t<Iterator> res = *this;
    res += n;
    return res;
}

template<class Iterator>
reverse_iterator_t<Iterator> reverse_iterator_t<Iterator>::operator - (difference_type n)const {
    reverse_iterator_t<Iterator> res = *this;
    res -= n;
    return res;
}


template <class Iterator>
bool operator == (const reverse_iterator_t<Iterator>& lhs, const reverse_iterator_t<Iterator>& rhs) {
    return lhs.cur_ == rhs.cur_;
}
template <class Iterator>
bool operator != (const reverse_iterator_t<Iterator>& lhs, const reverse_iterator_t<Iterator>& rhs) {
    return !(lhs == rhs);
}
template <class Iterator>
bool operator < (const reverse_iterator_t<Iterator>& lhs, const reverse_iterator_t<Iterator>& rhs) {
    return lhs.cur_ < rhs.cur_;
}
template <class Iterator>
bool operator > (const reverse_iterator_t<Iterator>& lhs, const reverse_iterator_t<Iterator>& rhs) {
    return lhs.cur_ > rhs.cur_;
}
template <class Iterator>
bool operator >= (const reverse_iterator_t<Iterator>& lhs, const reverse_iterator_t<Iterator>& rhs) {
    return !(lhs < rhs);
}
template <class Iterator>
bool operator <= (const reverse_iterator_t<Iterator>& lhs, const reverse_iterator_t<Iterator>& rhs) {
    return !(lhs > rhs);
}

template <class Iterator>
reverse_iterator_t<Iterator> operator + (
    typename reverse_iterator_t<Iterator>::difference_type n,
    const reverse_iterator_t<Iterator>& rev_it) {
    return rev_it + n;
}
template <class Iterator>
typename reverse_iterator_t<Iterator>::difference_type operator - (
    const reverse_iterator_t<Iterator>& lhs,
    const reverse_iterator_t<Iterator>& rhs) {
    return lhs.cur_ - rhs.cur_;
}

}
#endif