// #ifndef __MYSTL_VECTOR_IMPL_H
// #define __MYSTL_VECTOR_IMPL_H

// #include<iostream>

// namespace mystl {
// // destructor
// template<class T, class Alloc>
// vector<T, Alloc>::~vector() {
//     destroy_and_deallocate_all();
// }

// // constructor
// template<class T, class Alloc>
// vector<T, Alloc>::vector(const size_type n) {
//     allocate_and_fill(n, value_type());
// }
// template<class T, class Alloc>
// vector<T, Alloc>::vector(const size_type n, const value_type& value) {
//     allocate_and_fill(n, value);
// }
// template<class T, class Alloc>
// template<class InputIterator>
// vector<T, Alloc>::vector(InputIterator first, InputIterator last) {
//     vector_aux(first, last, typename std::is_integral<InputIterator>::type());
// }                                           // std::is_integral
// template<class T, class Alloc>
// vector<T, Alloc>::vector(const vector& v) {
//     allocate_and_copy(v.start_, v.finish_);
// }
// template<class T, class Alloc>
// vector<T, Alloc>::vector(vector&& v) {
//     start_ = v.start_;
//     finish_ = v.finish_;
//     end_of_storage_ = v.end_of_storage_;
// }

// // assignment
// template<class T, class Alloc>
// vector<T, Alloc>& vector<T, Alloc>::operator=(const vector& v) {
//     if(this != &v) {
//         allocate_and_copy(v.start_, v.finish_);
//     }
//     return *this;
// }
// template<class T, class Alloc>
// vector<T, Alloc>& vector<T, Alloc>::operator=(vector&& v) {
//     if(this != &v) {                            // how possible
//         destroy_and_deallocate_all();
//         start_ = v.start_;
//         finish_ = v.finish_;
//         end_of_storage_ = v.end_of_storagel;
//         v.start_ = v.finish_ = v.end_of_storage_ = 0;
//     }
//     return *this;
// }

// // volumn
// template<class T, class Alloc>
// void vector<T, Alloc>::resize(size_type n, value_type value) {
//     if(n < size()) {
//         data_allocator::destroy(start_ + n, finish_);
//         finish_ = start_ + n;
//     } else if(n > size() && n <= capacity()) {
//         auto len = n - size();
//         finish_ = mystl::uninitialized_fill_n(finish_, len, value);
//     } else if(n > capacity()) {
//         auto len = n - size();
//         T* new_start = data_allocator::allocate(get_new_capacity(len));
//         T* new_finish = mystl::uninitialized_copy(begin(), end(), new_start);
//         new_finish = mystl::uninitialized_fill_n(new_finish, len, value);
//         destroy_and_deallocate_all();
//         start_  = new_start;
//         finish_ = new_finish;
//         end_of_storage_ = start_ + n;
//     }
// }
// // ========================
// template<class T, class Alloc>
// void vector<T, Alloc>::reserve(size_type n) {
//     if(n <= capacity()) return ;
//     T* new_start = data_allocator::allocate(n);
//     T* new_finish = mystl::uninitialized_copy(begin(), end(), new_start);
//     destroy_and_deallocate_all();
//     start_ = new_start;
//     finish_ = new_finish;
//     end_of_storage_ = start_ + n;
// }

// // modify elements
// template<class T, class Alloc>
// typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(iterator position) {
//     return erase(position, position + 1);
// }
// template<class T, class Alloc>
// typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(iterator first, iterator last) {
//     difference_type len_of_tail = end() - last;
//     difference_type len_of_removed = last - first;
//     finish_ = finish_ - len_of_removed;
//     for(; len_of_tail != 0; --len_of_tail) {
//         auto tmp = (last - len_of_removed);
//         *tmp = *(last++);
//     }
//     return first;
// }

// template<class T, class Alloc>
// template<class InputIterator>
// void vector<T, Alloc>::reallocate_and_copy(iterator position, InputIterator first, InputIterator last) {
//     difference_type new_capacity = get_new_capacity(last - first);
//     T *new_start = data_allocator::allocate(new_capacity);
//     T *new_end_of_storage = new_start + new_capacity;
//     T *new_finish = mystl::uninitialized_copy(begin(), position, new_start);
//     new_finish = mystl::uninitialized_copy(first, last, new_finish);
//     new_finish = mystl::uninitialized_copy(position, end(), new_finish);
//     destroy_and_deallocate_all();
//     start_ = new_start;
//     finish_ = new_finish;
//     end_of_storage_ = new_end_of_storage;
// }

// template<class T, class Alloc>
// void vector<T, Alloc>::reallocate_and_fill(iterator position, const size_type& n, const value_type& value) {
//     difference_type new_capacity = get_new_capacity(n);
//     T *new_start = data_allocator::allocate(new_capacity);
//     T *new_end_of_storage = new_start + new_capacity;
//     T *new_finish = mystl::uninitialized_copy(begin(), position, new_start);
//     new_finish = mystl::uninitialized_fill_n(new_finish, n, value);
//     new_finish = mystl::uninitialized_copy(position, end(), new_finish);
//     destroy_and_deallocate_all();
//     start_ = new_start;
//     finish_ = new_finish;
//     end_of_storage_ = new_end_of_storage;
// }

// template<class T, class Alloc>
// template<class InputIterator>
// void vector<T, Alloc>::insert_aux(iterator position, InputIterator first,
//                                   InputIterator last, std::false_type) {
//     difference_type left = end_of_storage_ - finish_;
//     difference_type need = distance(first, last);
//     if(left >= need) {                          // 目前为止足够
//         if(finish_ - position > need) {         // 要移动的比要插入的多
//             mystl::uninitialized_copy(finish_ - need, finish_, finish_);
//             std::copy_backward(position, finish_ - need, finish_);
//             std::copy(first, last, position);
//         } else {
//             iterator tmp = mystl::uninitialized_copy(first + (finish_ - position), last, finish_);
//             mystl::uninitialized_copy(position, finish_, tmp);
//             std::copy(first, first + (finish_ - position), position);
//         }
//         finish_ += need;
//     } else {
//         reallocate_and_copy(position, first, last);
//     }
// }

// template<class T, class Alloc>
// template<class Integer>
// void vector<T, Alloc>::insert_aux(iterator position, Integer n, const value_type& value, std::true_type) {
//     assert(n != 0);
//     difference_type left = end_of_storage_ - finish_;
//     difference_type need = n;
//     if(left >= need) {
//         auto tmp = end() - 1;
//         for(; tmp - position >= 0 ; --tmp) {
//             construct(tmp + need, *tmp);
//         }
//         mystl::uninitialized_fill_n(position, n, value);
//         finish_ += need;
//     } else {
//         reallocate_and_fill(position, n, value);
//     }
// }

// template<class T, class Alloc>
// template<class InputIterator>
// void vector<T, Alloc>::insert(iterator position, InputIterator first, InputIterator last) {
//     insert_aux(position, first, last, typename std::is_integral<InputIterator>::type());
// }
// template<class T, class Alloc>
// void vector<T, Alloc>::insert(iterator position, const size_type& n, const value_type& value) {
//     insert_aux(position, n, value, typename std::is_integral<size_type>::type());
// }
// template<class T, class Alloc>
// typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(iterator position, const value_type& value) {
//     const auto index = position - begin();
//     insert(position, 1, value);
//     return begin() + index;                             // 看不懂这操作，直接return position不就行了
// }
// template<class T, class Alloc>
// void vector<T, Alloc>::push_back(const value_type& value) {
//     insert(end(), value);
// }

// // compare
// template<class T, class Alloc>
// bool vector<T, Alloc>::operator==(const vector& v) const {      // 运算符重载不用声明？
//     if(size() != v.size()) {
//         return false;
//     } else {
//         auto ptr1 = start_;
//         auto ptr2 = v.start_;
//         for(; ptr1 != finish_ && ptr2 != v.finish_; ++ptr1, ++ptr2) {
//             if(*ptr1 != *ptr2)
//                 return false;
//         }
//         return true;
//     }
// }
// template<class T, class Alloc>
// bool vector<T, Alloc>::operator!=(const vector& v) const {
//     return !(*this == v);
// }
// template<class T, class Alloc>
// bool operator==(const vector<T, Alloc>& v1, const vector<T, Alloc>& v2) {
//     return v1.operator == (v2);
// }
// template<class T, class Alloc>
// bool operator!=(const vector<T, Alloc>& v1, const vector<T, Alloc>& v2) {
//     return !(v1 == v2);
// }

// template<class T, class Alloc>
// void vector<T, Alloc>::shrink_to_fit() {
//     T* t = (T*)data_allocator::allocate(size());
//     finish_ = mystl::uninitialized_copy(start_, finish_, t);
//     data_allocator::deallocate(start_, capacity());
//     start_ = t;
//     end_of_storage_ = finish_;
// }

// template<class T, class Alloc>
// void vector<T, Alloc>::clear() {
//     data_allocator::destroy(start_, finish_);
//     finish_ = start_;
// }

// template<class T, class Alloc>
// void vector<T, Alloc>::swap(vector& v) {
//     if(this != &v) {
//         mystl::swap(start_, v.start_);
//         mystl::swap(finish_, v.finish_);
//         mystl::swap(end_of_storage_, v.end_of_storage_);
//     }
// }

// template<class T, class Alloc>
// void vector<T, Alloc>::pop_back() {
//     --finish_;
//     data_allocator::destroy(finish_);
// }

// template<class T, class Alloc>
// void vector<T, Alloc>::destroy_and_deallocate_all() {
//     if(capacity() != 0) {
//         data_allocator::destroy(start_, finish_);
//         data_allocator::deallocate(start_, capacity());
//     }
// }

// template<class T, class Alloc>
// void vector<T, Alloc>::allocate_and_fill(const size_type n, const value_type& value) {
//     start_ = data_allocator::allocate(n);
//     mystl::uninitialized_fill_n(start_, n, value);
//     finish_ = end_of_storage_ = start_ + n;
// }

// template<class T, class Alloc>
// template<class InputIterator>
// void vector<T, Alloc>::allocate_and_copy(InputIterator first, InputIterator last) {
//     start_ = data_allocator::allocate(last - first);
//     finish_ = mystl::uninitialized_copy(first, last, start_);
//     end_of_storage_ = finish_;
// }

// template<class T, class Alloc>
// template<class InputIterator>
// void vector<T, Alloc>::vector_aux(InputIterator first, InputIterator last, std::false_type) {
//     allocate_and_copy(first, last);
// }

// template<class T, class Alloc>
// template<class Integer>
// void vector<T, Alloc>::vector_aux(Integer n, const value_type& value, std::true_type) {
//     allocate_and_fill(n, value);
// }

// template<class T, class Alloc>
// typename vector<T, Alloc>::size_type vector<T, Alloc>::get_new_capacity(size_type len) const {
//     size_type old_cap = end_of_storage_ - start_;
//     auto res = mystl::max(old_cap, len);
//     size_type new_cap = (old_cap != 0 ? (old_cap + res) : len);
//     return new_cap;
// }

// }
// #endif