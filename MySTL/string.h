#ifndef __MYSTL_STRING_H
#define __MYSTL_STRING_H

#include "allocator.h"
#include "reverse_iterator.h"
#include "uninitialized.h"
#include "util.h"

#include<cstring>
#include<type_traits>

namespace mystl {

class string {
public:
    typedef char value_type;
    typedef char* iterator;
    typedef const char * const_iterator;
    typedef reverse_iterator_t<char*> reverse_iterator;
    typedef reverse_iterator_t<const char*> const_reverse_iterator;
    typedef char& reference;
    typedef const char& const_reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef mystl::allocator<char> data_allocator;
    static const size_t npos = -1;                  // greatest positive value of size_t
private:
    char *start_;
    char *finish_;
    char *end_of_storage_;
public:
    // default constructor
    string(): start_(0), finish_(0), end_of_storage_(0) {}
    // copy constructor
    string(const string& str);
    string(string&& str);
    // other construtor
    string(const string& str, size_t pos, size_t len = npos);       // len为什么是npos
    string(const char* s);
    string(const char* s, size_t n);
    string(size_t n, char c);
    template<class InputIterator>
    string(InputIterator first, InputIterator last);

    // destructor
    ~string();

    // assignment
    string& operator=(const string& str);
    string& operator=(string&& str);
    string& operator=(const char *s);
    string& operator=(char c);

    // iterator
    iterator begin() {
        return start_;
    }
    const_iterator begin() const {
        return start_;
    }
    iterator end() {
        return finish_;
    }
    const_iterator end() const {
        return finish_;
    }
    reverse_iterator rbegin() {
        return reverse_iterator(finish_);
    }
    const_reverse_iterator rbegin() const {
        return const_reverse_iterator(finish_);
    }
    reverse_iterator rend() {
        return reverse_iterator(start_);
    }
    const_reverse_iterator rend() const {
        return const_reverse_iterator(start_);
    }
    const_iterator cbegin() const {
        return start_;
    }
    const_iterator cend() const {
        return finish_;
    }
    const_reverse_iterator crbegin() const {
        return const_reverse_iterator(finish_);
    }
    const_reverse_iterator crend() const {
        return const_reverse_iterator(start_);
    }

    // size
    size_t size() const {
        return finish_ - start_;
    }
    size_t length() const {
        return size();
    }
    size_t capacity() const {
        return end_of_storage_ - start_;
    }
    void clear() {
        data_allocator::destroy(start_, finish_);
        start_ = finish_;
    }
    bool empty() const {
        return start_ == finish_;
    }
    void resize(size_t n);
    void resize(size_t n, char c);
    void reserve(size_t n = 0);
    void shrink_to_fit() {
        data_allocator::deallocate(finish_, end_of_storage_ - finish_);
        end_of_storage_ = finish_;
    }

    // visit element
    char& operator[](size_t pos) {
        return *(start_ + pos);
    }
    const char& operator[](size_t pos) const {
        return *(start_ + pos);
    }
    char& back() {
        return *(finish_ - 1);
    }
    const char& back() const {
        return *(finish_ - 1 );
    }
    char& front() {
        return *(start_);
    }
    const char& front() const {
        return *(start_);
    }

    // modify element
    // add
    void push_back(char c) {
        insert(end(), c);
    }
    string& insert(size_t pos, const string& str);
    string& insert(size_t pos, const string& str, size_t subpos, size_t sublen = npos);
    string& insert(size_t pos, const char* s);
    string& insert(size_t pos, const char* s, size_t n);
    string& insert(size_t pos, size_t n, char c);
    iterator insert(iterator p, size_t n, char c);
    iterator insert(iterator p, char c);
    template<class InputIterator>
    iterator insert(iterator p, InputIterator first, InputIterator last);

    string& append(const string& str);
    string& append(const string& str, size_t subpos, size_t sublen = npos);
    string& append(const char* s);
    string& append(const char* s, size_t n);
    string& append(size_t n, char c);
    template<class InputIterator>
    string& append(InputIterator first, InputIterator last);

    string& operator+=(const string& str);
    string& operator+=(const char* s);
    string& operator+=(char c);

    // remove
    void pop_back() {
        erase(end() - 1, end());
    }
    string& erase(size_t pos = 0, size_t len = npos);
    iterator erase(iterator p);
    iterator erase(iterator first, iterator last);

    // replace
    string& replace(size_t pos, size_t len, const string& str);
    string& replace(iterator i1, iterator i2, const string& str);
    string& replace(size_t pos, size_t len, const string& str, size_t subpos, size_t sublen = npos);
    string& replace(size_t pos, size_t len, const char* s);
    string& replace(iterator i1, iterator i2, const char* s);
    string& replace(size_t pos, size_t len, const char* s, size_t n);
    string& replace(iterator i1, iterator i2, const char* s, size_t n);
    string& replace(size_t pos, size_t len, size_t n, char c);
    string& replace(iterator i1, iterator i2, size_t n, char c);
    template<class InputIterator>
    string& replace(iterator i1, iterator i2, InputIterator first, InputIterator last);

    // find
    size_t find(const string &str, size_t pos = 0) const;
    size_t find(const char *s, size_t pos = 0) const;
    size_t find(const char *s, size_t pos, size_t n) const;
    size_t find(char c, size_t pos = 0) const;
    size_t rfind(const string &str, size_t pos = npos) const;
    size_t rfind(const char *s, size_t pos = npos) const;
    size_t rfind(const char *s, size_t pos, size_t n) const;
    size_t rfind(char ch, size_t pos = npos) const;
    size_t find_first_of(const string& str, size_t pos = 0) const;
    size_t find_first_of(const char* s, size_t pos = 0) const;
    size_t find_first_of(const char* s, size_t pos, size_t n) const;
    size_t find_first_of(char c, size_t pos = 0) const;
    size_t find_last_of(const string& str, size_t pos = npos) const;
    size_t find_last_of(const char* s, size_t pos = npos) const;
    size_t find_last_of(const char* s, size_t pos, size_t n) const;
    size_t find_last_of(char c, size_t pos = npos) const;
    size_t find_first_not_of(const string& str, size_t pos = 0) const;
    size_t find_first_not_of(const char* s, size_t pos = 0) const;
    size_t find_first_not_of(const char* s, size_t pos, size_t n) const;
    size_t find_first_not_of(char c, size_t pos = 0) const;
    size_t find_last_not_of(const string& str, size_t pos = npos) const;
    size_t find_last_not_of(const char* s, size_t pos = npos) const;
    size_t find_last_not_of(const char* s, size_t pos, size_t n) const;
    size_t find_last_not_of(char c, size_t pos = npos) const;

    // compare
    int compare(const string& str) const;
    int compare(size_t pos, size_t len, const string &str) const;
    int compare(size_t pos, size_t len, const string &str, size_t subpos, size_t sublen = npos)const;
    int compare(const char *s) const;
    int compare(size_t pos, size_t len, const char *s) const;
    int compare(size_t pos, size_t len, const char *s, size_t n) const;

    // other func
    void swap(string& str) {
        mystl::swap(start_, str.start_);
        mystl::swap(finish_, str.finish_);
        mystl::swap(end_of_storage_, str.end_of_storage_);
    }
    size_t copy(char *s, size_t len, size_t pos = 0) const {        // copy
        auto ptr = mystl::uninitialized_copy(begin() + pos, begin() + pos + len, s);
        return (size_t)(ptr - s);
    }
    string substr(size_t pos = 0, size_t len = npos) const {
        len = change_npos_param(len, size(), pos);
        return string(begin() + pos, begin() + pos + len);
    }

private:
    void move_data(string &str);
    template<class InputIterator>
    iterator insert_aux_copy(iterator p, InputIterator first, InputIterator last);
    iterator insert_aux_fill(iterator p, size_t n, value_type c);
    size_t get_new_capacity(size_t len) const;
    void destroy_and_deallocate();

    void allocate_and_fill(size_t n, char c);
    template<class InputIterator>
    void allocate_and_copy(InputIterator first, InputIterator last);

    void string_aux(size_t n, char c, std::true_type);
    template<class InputIterator>
    void string_aux(InputIterator first, InputIterator last, std::false_type);

    size_t rfind_aux(const_iterator cit, size_t pos, size_t len, size_t cond) const;
    size_t find_aux(const_iterator cit, size_t pos, size_t len, size_t cond) const;

    int compare_aux(size_t pos, size_t len, const_iterator cit, size_t subpos, size_t sublen) const;
    bool is_contained(char c, const_iterator first, const_iterator last) const;
    size_t change_npos_param(size_t param, size_t med, size_t m) const;
public:
    friend std::ostream& operator<<(std::ostream& os, const string&str);
    friend std::istream& operator>> (std::istream& is, string& str);
    friend string operator+ (const string& lhs, const string& rhs);
    friend string operator+ (const string& lhs, const char* rhs);
    friend string operator+ (const char* lhs, const string& rhs);
    friend string operator+ (const string& lhs, char rhs);
    friend string operator+ (char lhs, const string& rhs);
    friend bool operator== (const string& lhs, const string& rhs);
    friend bool operator== (const char*   lhs, const string& rhs);
    friend bool operator== (const string& lhs, const char*   rhs);
    friend bool operator!= (const string& lhs, const string& rhs);
    friend bool operator!= (const char*   lhs, const string& rhs);
    friend bool operator!= (const string& lhs, const char*   rhs);
    friend bool operator<  (const string& lhs, const string& rhs);
    friend bool operator<  (const char*   lhs, const string& rhs);
    friend bool operator<  (const string& lhs, const char*   rhs);
    friend bool operator<= (const string& lhs, const string& rhs);
    friend bool operator<= (const char*   lhs, const string& rhs);
    friend bool operator<= (const string& lhs, const char*   rhs);
    friend bool operator>  (const string& lhs, const string& rhs);
    friend bool operator>  (const char*   lhs, const string& rhs);
    friend bool operator>  (const string& lhs, const char*   rhs);
    friend bool operator>= (const string& lhs, const string& rhs);
    friend bool operator>= (const char*   lhs, const string& rhs);
    friend bool operator>= (const string& lhs, const char*   rhs);
    friend void swap(string& x, string& y);
    friend std::istream& getline(std::istream& is, string& str, char delim);
    friend std::istream& getline(std::istream& is, string& str);
};

// ==================== template ====================
template<class InputIterator>
string::string(InputIterator first, InputIterator last) {
    string_aux(first, last, typename std::is_integral<InputIterator>::type());
}

template<class InputIterator>
void string::string_aux(InputIterator first, InputIterator last, std::false_type) {
    allocate_and_copy(first, last);
}

template<class InputIterator>
string::iterator string::insert_aux_copy(iterator p, InputIterator first, InputIterator last) {
    auto len = distance(last, first);
    auto new_capacity = get_new_capacity(len);
    iterator new_start = data_allocator::allocate(new_capacity);
    iterator new_finish = mystl::uninitialized_copy(start_, p, new_start);
    new_finish = mystl::uninitialized_copy(first, last, new_finish);
    auto ret = new_finish;
    new_finish = mystl::uninitialized_copy(last, end_of_storage_, new_finish);
    destroy_and_deallocate();
    start_ = new_start;
    finish_ = new_finish;
    end_of_storage_ = start_ + new_capacity;
    return ret;
}

template<class InputIterator>
string::iterator string::insert(iterator p, InputIterator first, InputIterator last) {
    auto left  = capacity() - size();
    auto len = distance(first, last);
    if(len <= left) {
        for(iterator it = finish_ - 1; it >= p; --it) {
            *(it + len) = *it;
        }
        uninitialized_copy(first, last, p);
        finish_ += len;
        return (p + len);
    } else {
        return insert_aux_copy(p, first, last);
    }
}

template<class InputIterator>
string& string::append(InputIterator first, InputIterator last) {
    insert(end(), first, last);
    return *this;
}

template<class InputIterator>
string& string::replace(iterator i1, iterator i2, InputIterator first, InputIterator last) {
    auto ptr = erase(i1, i2);
    insert(ptr, first, last);
    return *this;
}

template<class InputIterator>
void string::allocate_and_copy(InputIterator first, InputIterator last) {
    start_ = data_allocator::allocate(distance(first, last));
    finish_ = uninitialized_copy(first, last, start_);
    end_of_storage_ = finish_;
}

// =================== nontemplate =================
using string::npos;             // using

string::string(const string& str) {
    allocate_and_copy(str.start_, str.finish_);
}

string::string(string&& str) {
    move_data(str);                             // move_data
}

string::string(const string &str, size_t pos, size_t len) {
    len = change_npos_param(len, str.size(), pos);
    allocate_and_copy(str.start_ + pos, str.start_ + pos + len);
}

string::string(const char *s) {
    allocate_and_copy(s, s + strlen(s));        // char *的string，strlen
}

string::string(const char *s, size_t n) {
    allocate_and_copy(s, s + n);
}

string::string(size_t n, char c) {
    allocate_and_fill(n, c);
}

string::~string() {
    destroy_and_deallocate();
}

// ------------- assignment
string& string::operator=(const string& str) {
    if(this != &str) {
        destroy_and_deallocate();
        allocate_and_copy(str.start_, str.finish_);
    }
    return *this;
}

string& string::operator=(string&& str) {
    if(this != &str) {
        move_data(str);
    }
    return *this;
}

string& string::operator=(const char *s) {
    destroy_and_deallocate();
    allocate_and_copy(s, s + strlen(s));
    return *this;
}

string& string::operator=(char c) {
    destroy_and_deallocate();
    allocate_and_fill(1, c);
    return *this;
}

// ------------------- resize & reserve
void string::resize(size_t n) {
    resize(n, value_type());
}

void string::resize(size_t n, char c) {           // 3 situations (about finish_)
    if(n < size()) {
        data_allocator::destroy(start_ + n, finish_);
        finish_ = start_ + n;
    } else if(n > size() && n <= capacity()) {
        auto len = n - size();
        finish_ = uninitialized_fill_n(finish_, len, c);
    } else if(n > capacity()) {
        auto len = n - size();
        iterator new_start = data_allocator::allocate(get_new_capacity(len));
        iterator new_finish = uninitialized_copy(begin(), end(), new_start);
        new_finish = uninitialized_fill_n(new_finish, len, c);
        destroy_and_deallocate();
        start_ = new_start;
        finish_ = new_finish;
        end_of_storage_ = new_start + n;
    }
}

void string::reserve(size_t n) {                // about end_of_storage
    if(n <= capacity()) return ;
    iterator new_start = data_allocator::allocate(n);
    iterator new_finish = uninitialized_copy(begin(), end(), new_start);
    destroy_and_deallocate();
    start_ = new_start;
    finish_ = new_finish;
    end_of_storage_ = start_ + n;
}

// --------------------- insert(iterator)
string& string::insert(size_t pos, const string& str) {
    insert(start_ + pos, str.begin(), str.end());
    return *this;
}

string& string::insert(size_t pos, const string& str, size_t subpos, size_t sublen) {
    sublen  = change_npos_param(sublen, str.size(), subpos);
    insert(begin() + pos, str.begin() + subpos, str.begin() + subpos + sublen);
    return *this;
}

string& string::insert(size_t pos, const char *s) {
    insert(start_ + pos, s, s + strlen(s));
    return *this;
}

string& string::insert(size_t pos, const char *s, size_t n) {
    insert(start_ + pos, s, s + n);
    return *this;
}

// --------------------- insert (n char )
string::iterator string::insert_aux_fill(iterator p, size_t n, value_type c) {
    auto new_capacity = get_new_capacity(n);
    iterator new_start = data_allocator::allocate(new_capacity);
    iterator new_finish = mystl::uninitialized_copy(start_, p, new_start);
    new_finish = mystl::uninitialized_fill_n(new_finish, n, c);
    auto ret = new_finish;
    new_finish = mystl::uninitialized_copy(p, finish_, new_finish);
    destroy_and_deallocate();
    start_ = new_start;
    finish_ = new_finish;
    end_of_storage_ = start_ + new_capacity;
    return ret;
}

string& string::insert(size_t pos, size_t n, char c) {
    insert(begin() + pos, n, c);
    return *this;
}

string::iterator string::insert(iterator p, size_t n, char c) {
    auto left = capacity() - size();
    if(n <= left) {
        for(iterator it = finish_ - 1; it >= p; --it) {
            *(it + n) = *it;
        }
        uninitialized_fill_n(p, n, c);
        finish_ += n;
        return (p + n);
    } else {
        return insert_aux_fill(p, n, c);
    }
}

string::iterator string::insert(iterator p, char c) {
    return insert(p, 1, c);
}

// --------------------- operator+=
string& string::operator+=(const string& str) {
    insert(size(), str);
    return *this;
}

string& string::operator+=(const char *s) {
    insert(size(), s);
    return *this;
}

string& string::operator+=(char c) {
    insert(end(), c);
    return *this;
}

// -------------------- append
string& string::append(const string& str) {
    (*this) += str;
    return *this;
}

string& string::append(const string& str, size_t subpos, size_t sublen) {
    insert(size(), str, subpos, sublen);
    return *this;
}

string& string::append(const char *s) {
    (*this) += s;
    return *this;
}

string& string::append(const char *s, size_t n) {
    insert(size(), s, n);
    return *this;
}

string& string::append(size_t n, char c) {
    insert(end(), n, c);
    return *this;
}

// -------------------- erase
string::iterator string::erase(iterator first, iterator last) {
    size_t len = finish_ - last;
    for(auto i = 0; i < len; ++i) {
        *(first + i) = *(last + i);
    }
    data_allocator::destroy(first + len, finish_);
    finish_ = first + len;
    return first;
}

string& string::erase(size_t pos, size_t len) {
    len = change_npos_param(len, size(), pos);
    erase(begin() + pos, begin() + pos + len);
    return *this;
}

string::iterator string::erase(iterator p) {
    return erase(p, p + 1);
}

// ---------------------- replace
string& string::replace(size_t pos, size_t len, const string& str) {
    return replace(begin() + pos, begin() + pos + len, str.begin(), str.end());
}

string& string::replace(iterator i1, iterator i2, const string& str) {
    return replace(i1, i2, str.begin(), str.end());
}

string& string::replace(size_t pos, size_t len, const string& str, size_t subpos, size_t sublen ) {
    sublen = change_npos_param(sublen, str.size(), subpos);
    return replace(begin() + pos, begin() + pos + len, str.begin() + subpos, str.begin() + subpos + sublen);
}

string& string::replace(size_t pos, size_t len, const char *s) {
    return replace(begin() + pos, begin() + pos + len, s, s + strlen(s));
}

string& string::replace(iterator i1, iterator i2, const char *s) {
    return replace(i1, i2, s, s + strlen(s));
}

string& string::replace(size_t pos, size_t len, const char *s, size_t n) {
    return replace(begin() + pos, begin() + pos + len, s, s + n);
}

string& string::replace(iterator i1, iterator i2, const char *s, size_t n) {
    return replace(i1, i2, s, s + n);
}

string& string::replace(iterator i1, iterator i2, size_t n, char c) {
    auto pos = erase(i1, i2);
    insert(pos, n, c);
    return *this;
}
string& string::replace(size_t pos, size_t len, size_t n, char c) {
    return replace(begin() + pos, begin() + pos + len, n, c);
}

// --------------------------- find
size_t string::find_aux(const_iterator cit, size_t pos, size_t len, size_t cond) const {
    size_t i, j;
    for(i = pos; i != cond; ++i) {
        for(j = 0; j != len; ++j) {
            if(*(begin() + i + j) != cit[j])
                break;
        }
        if(j == len)
            return i;
    }
    return npos;
}

size_t string::find(const string &str, size_t pos) const {
    size_t len = str.size();
    if(size() - pos < len) return npos;             // str的长度可以直接求，节省时间
    return find_aux(str.cbegin(), pos, len, size());
}

size_t string::find(const char *s, size_t pos, size_t n) const {
    return find_aux(s, pos, n, size());
}

size_t string::find(const char *s, size_t pos) const {
    return find(s, pos, strlen(s));
}

size_t string::find(char c, size_t pos) const {
    for(auto cit = cbegin() + pos; cit != cend(); ++cit) {
        if(*cit == c) return cit - cbegin();
    }
    return npos;
}

// ----------------------- rfind
size_t string::rfind_aux(const_iterator cit, size_t pos, size_t len, size_t cond) const {
    size_t i, j;
    for(i = pos; i >= cond; --i) {                          // 起点在pos或之前
        for(j = 0; j != len; ++j) {
            if(*(begin() + i + j) != cit[j])
                break;
        }
        if(j == len)
            return i;
    }
    return npos;
}

size_t string::rfind(const string& str, size_t pos) const {
    size_t len = str.size();
    pos = change_npos_param(pos, size(), len);              // > size()-len不可能匹配
    return rfind_aux(str.begin(), pos, len, 0);
}

size_t string::rfind(const char *s, size_t pos )const {
    size_t len = str.size();
    pos = change_npos_param(pos, size(), len);
    return rfind_aux(s, pos, len, 0)
}
size_t string::rfind(const char*s, size_t pos, size_t n) const {
    // pos没有npos默认值
    return rfind_aux(s, pos, n, 0);
}

// ------------------------ find_first_of
size_t string::find_first_of(const char *s, size_t pos, size_t n) const {
    for(size_t i = pos; i != size(); ++i) {
        if(is_contained((*this)[i], s, s + n))
            return i;
    }
    return npos;
}
size_t string::find_first_of(const string& str, size_t pos) const {
    return find_first_of(str.begin(), pos, str.size());            // should be this
}

size_t string::find_first_of(const char *s, size_t pos) const {
    return find_first_of(s, pos, strlen(s));
}

size_t string::find_first_of(char c, size_t pos) const {
    return find(c, pos);
}

// ------------------------- find_first_not_of
size_t string::find_first_not_of(const char *s, size_t pos, size_t n) const {
    for(size_t i = pos; i != size(); ++i) {
        if(!is_contained((*this)[i], s, s + n))
            return i;
    }
    return npos;
}

size_t string::find_first_not_of(const string& str, size_t pos) const {
    return find_first_not_of(str.begin(), pos, str.size());            // should be this
}

size_t string::find_first_not_of(const char *s, size_t pos) const {
    return find_first_not_of(s, pos, strlen(s));
}

size_t string::find_first_not_of(char c, size_t pos) const {
    for(size_t i = pos; i != size(); ++i) {
        if((*this)[i] != c)
            return i;
    }
    return npos;
}

// ------------------------ find_last_of
size_t string::find_last_of(const char *s, size_t pos, size_t n) const {
    for(size_t i = pos; i >= 0; --i) {
        if(is_contained((*this)[i], s, s + n))
            return i;
    }
    return npos;
}

size_t string::find_last_of(const string& str, size_t pos) const {
    pos = change_npos_param(pos, size(), 1);
    return find_last_of(str.begin(), pos, str.size());
}

size_t string::find_last_of(const char *s, size_t pos) const {
    pos = change_npos_param(pos, size(), 1);
    return find_last_of(s, pos, strlen(s));
}

size_t string::find_last_of(char c, size_t pos) const {
    return rfind(c, pos);
}

// ------------------------ find_last_not_of
size_t string::find_last_not_of(const char *s, size_t pos, size_t n) const {
    for(size_t i = pos; i >= 0; --i) {
        if(!is_contained((*this)[i], s, s + n))
            return i;
    }
    return npos;
}

size_t string::find_last_not_of(const string& str, size_t pos) const {
    pos = change_npos_param(pos, size(), 1);
    return find_last_not_of(str.begin(), pos, str.size());
}

size_t string::find_last_not_of(const char *s, size_t pos) const {
    pos = change_npos_param(pos, size(), 1);
    return find_last_not_of(s, pos, strlen(s));
}

size_t string::find_last_not_of(char c, size_t pos) const {
    pos = change_npos_param(pos, size(), 1);
    for(size_t i = pos; i >= 0; --i) {
        if((*this)[i] != c)
            return i;
    }
    return npos;
}

// ------------------------ compare
int string::compare_aux(size_t pos, size_t len, const_iterator cit, size_t subpos, size_t sublen) const {
    size_t i, j;
    for(i = 0, j = 0; i != len && j != sublen; ++i, ++j) {
        if((*this)[pos + i] < cit[subpos + j])
            return -1;
        else if((*this)[pos + i] > cit[subpos + j])
            return 1;
    }
    if(i == len && j == sublen)
        return 0;
    else if(i == len) return -1;
    else return 1;
}

int string::compare(const string& str) const {
    return compare_aux(0, size(), str.cbegin(), 0, str.size());
}

int string::compare(size_t pos, size_t len, const string& str) const {
    return compare_aux(pos, len, str.cbegin(), 0, str.size());
}

int string::compare(size_t pos, size_t len, const string& str, size_t subpos, size_t sublen) const {
    sublen = change_npos_param(sublen, str.size(), subpos);
    return compare_aux(pos, len, str.cbegin(), subpos, sublen);
}

int string::compare(const char *s) const {
    return compare_aux(0, size(), s, 0, strlen(s));
}

int string::compare(size_t pos, size_t len, const char *s) const {
    return compare_aux(pos, len, s, 0, strlen(s));
}

int string::compare(size_t pos, size_t len, const char *s, size_t n) const {
    return compare_aux(pos, len, s, 0, n);
}

// ------------------------ operator
std::ostream& operator<<(std::ostream& os, const string &str) const {
    for(auto ch : str) {
        os << ch;
    }
    return os;
}

std::istream& operator>>(std::istream& is, const string& str) const {
    char ch;
    string::size_type old_size = str.size(), index = 0;
    bool has_prev_blank = false;
    while(is.get(ch)) {
        if(isblank(ch) || ch == '\n')
            has_prev_blank = true;
        else break;
    }
    is.putback(ch);                     // 把之前的字符放回流中
    str.clear();                        // 清空字符串
    while(is.get(ch)) {
        if(ch != EOF && !isblank(ch) && ch != '\n') {
            str.push_back(ch);          // 一个个塞进去
        } else break;
    }
    return is;
}

string operator+(const string& lhs, const string& rhs) {
    string res(lhs);
    return res += rhs;
}

string operator+(const string& lhs, const char *rhs) {
    string res(lhs);
    return res += rhs;
}

string operator+(const char *lhs, const string& rhs) {
    string res(lhs);
    return res += rhs;
}

string operator+(const string& lhs, char rhs) {
    string res(lhs);
    return res += rhs;
}

string operator+(char lhs, const string &rhs) {
    string res(1, lhs);
    return res += rhs;
}

bool operator==(const string& lhs, const string& rhs) {
    if(lhs.size() == rhs.size()) {
        for(auto cit1 = lhs.cbegin(), cit2 = rhs.cbegin();
                cit1 != lhs.cend() && cit2 != rhs.cen(); ++cit1, ++cit2) {
            if(*cit1 != *cit2) return false;
        }
        return true;
    }
    return false;
}

bool operator==(const string& lhs, const char *rhs) {
    size_t len = strlen(rhs);
    if(lhs.size() == len) {
        const char *cit2 = rhs;
        for(auto cit1 = lhs.cbegin(); cit1 != lhs.cend() && cit2 != rhs + len; ++cit1, ++cit2) {
            if(*cit1 != *cit2) return false;
        }
        return true;
    }
    return false;
}

bool operator!=(const string& lhs, const string &rhs) {
    return !(lhs == rhs);
}

bool operator!=(const string& lhs, const char *rhs) {
    return !(lhs == rhs);
}

bool operator!=(const char *lhs, const string& rhs) {
    return !(lhs == rhs);
}

template<class Iterator1, class Iterator2>
bool less_aux(Iterator1 first1, Iterator1 last1, Iterator2 first2, Iterator2 last2) {
    for(; first1 != last1 && first2 != last2; ++first1, ++first2) {
        if(*first1 < *first2) return true;
    }
    if(first1 == last1 && first2 != last2)
        return true;
    else
        return false;
}

bool operator<(const string& lhs, const string& rhs) {
    return less_aux(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
}

bool operator<(const string& lhs, const char *rhs) {
    return less_aux(lhs.cbegin(), lhs.cend(), rhs, rhs + strlen(rhs));
}

bool operator<(const char *lhs, const string &rhs) {
    return less_aux(lhs, lhs + str(lhs), rhs.cbegin(), rhs.cend())l
}

bool operator>=(const string& lhs, const string& rhs) {
    return !(lhs < rhs);
}

bool operator>=(const string& lhs, const char *rhs) {
    return !(lhs < rhs);
}

bool operator>=(const char *lhs, const string& rhs) {
    return !(lhs < rhs);
}

template<class Iterator1, class Iterator2>
bool greater_aux(Iterator1 first1, Iterator1 last1, Iterator2 first2, Iterator2 last2) {
    for(; first1 != last1 && first2 != last2; ++first1, ++first2) {
        if(*first1 > *first2) return true;
    }
    if(first1 != last1 && first2 == last2)
        return true;
    else
        return false;
}

bool operator>(const string& lhs, const string& rhs) {
    return greater_aux(lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend());
}

bool operator>(const string& lhs, const char *rhs) {
    return greater_aux(lhs.cbegin(), lhs.cend(), rhs, rhs + strlen(rhs));
}

bool operator>(const char *lhs, const string& rhs) {
    return greater_aux(lhs, lhs + strlen(lhs), rhs.cbegin(), rhs.cend());
}

bool operator<=(const string& lhs, const string& rhs) {
    return !(lhs > rhs);
}

bool operator<=(const string& lhs, const char *rhs) {
    return !(lhs > rhs);
}

bool operator<=(const char *lhs, const string& rhs) {
    return !(lhs > rhs);
}

// ----------------------- getline
std::istream& getline(std::istream& is, string& str) {
    return getline(is, str, '\n');
}

std::istream& getline(std::istream& is, string& str, char delim) {
    char ch;
    str.clear();
    while(is.get(ch)) {
        if(ch == delim)
            break;
        else
            str.push_back(ch);
    }
    return is;
}

// ------------------------ swap
void swap(string& lhs, string &rhs) {
    lhs.swap(rhs);
}

// ------------------------ other private
void string::move_data(string& str) {
    start_ = str.start_;
    finish_ = str.finish_;
    end_of_storage_ = str.end_of_storage_;
    str.start_ = str.finish_ = str.end_of_storage_ = 0;
}

string::size_type string::get_new_capacity(size_type len) const {
    size_type old_capacity = end_of_storage_ - start_;
    auto res = mystl::max(old_capacity, len);
    auto new_capacity = old_capacity + res;             // 最少是两倍
    return new_capacity;
}

void string::allocate_and_fill(size_t n, char c) {
    start_ = data_allocator::allocate(n);
    finish_ = mystl::uninitialized_fill_n(start_, n, c);
    end_of_storage_ = finish_;
}

void string::string_aux(size_t n, char c, std::true_type) {
    allocate_and_fill(n, c);
}

void string::destroy_and_deallocate() {
    data_allocator::destroy(start_, finish_);
    data_allocator::deallocate(start_, end_of_storage_ - start_);
}

bool string::is_contained(char c, const_iterator first, const_iterator last) const {
    for(auto cit = first; cit != last; ++cit) {
        if(*cit == c)
            return true;
    }
    return false;
}

size_t string::change_npos_param(size_t param, size_t med, size_t m) const {
    return (param == npos ? med - m : param);
}



}
#endif
