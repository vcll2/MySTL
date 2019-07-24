#ifndef __MYSTL_ALLOC_H
#define __MYSTL_ALLOC_H

#include <cstdlib>

namespace mystl {

class alloc {
private:
    enum EAlign {ALIGN = 8};
    enum EMaxBytes {MAXBYTES = 128};
    enum ENFreeLists {NFREELISTS = (EMaxBytes::MAXBYTES / EAlign::ALIGN )};
    enum ENObjs {NOBJS = 20};

private:
    union obj {
        union obj* next;
        char client[1];
    };

    static obj *free_list[ENFreeLists::NFREELISTS];

private:
    static char *start_free;
    static char *end_free ;
    static size_t heap_size ;

private:
    static size_t ROUND_UP(size_t bytes) {
        return ((bytes + EAlign::ALIGN - 1) & ~(EAlign::ALIGN - 1));
    }
    static size_t FREELIST_INDEX(size_t bytes) {
        return (((bytes) + EAlign::ALIGN - 1) / EAlign::ALIGN - 1);
    }
    static void *refill(size_t bytes) {
        size_t nobjs = ENObjs::NOBJS;
        char *chunk = chunk_alloc(bytes, nobjs);
        obj **my_free_list = 0;
        obj *result = 0;
        obj *current_obj = 0, *next_obj = 0;
        if(nobjs == 1) {
            return chunk;
        } else {
            my_free_list = free_list + FREELIST_INDEX(bytes);
            result = (obj*)chunk;
            next_obj = *my_free_list = (obj*)(chunk + bytes);
            for(int i = 1;; ++i) {
                current_obj = next_obj;
                next_obj = (obj*)((char *)next_obj + bytes);
                if(nobjs - 1 == i) {
                    current_obj->next = 0;
                    break;
                } else {
                    current_obj->next = next_obj;
                }
            }
            return result;
        }
    }
    static char *chunk_alloc(size_t bytes, size_t& nobjs) {
        char *result;
        size_t total_bytes = bytes * nobjs;
        size_t bytes_left = end_free - start_free;
        if(bytes_left >= total_bytes) {
            result = start_free;
            start_free += total_bytes;
            return result;
        } else if(bytes_left >= bytes) {
            nobjs = bytes_left / bytes;
            total_bytes = bytes * nobjs;
            result = start_free;
            start_free += total_bytes;
            return result;
        } else {
            size_t bytes_to_get = 2 * total_bytes + ROUND_UP(heap_size >> 4);
            if(bytes_left > 0) {
                obj **my_free_list = free_list + FREELIST_INDEX(bytes_left);
                ((obj *)start_free)->next = *my_free_list;
                (*my_free_list)->next = (obj *)start_free;
            }
            start_free = (char *)malloc(bytes_to_get);
            if(!start_free) {
                obj **my_free_list, *p;
                for(int i = bytes; i <= EMaxBytes::MAXBYTES; i += EAlign::ALIGN) {
                    my_free_list = free_list + FREELIST_INDEX(i);
                    p = *my_free_list;
                    if(p != 0) {
                        *my_free_list = p->next;
                        start_free = (char*)p;
                        end_free = start_free + i;
                        return chunk_alloc(bytes, nobjs);
                    }
                }
                end_free = 0;
                //oom
            }
            heap_size += bytes_to_get;
            end_free = start_free + bytes_to_get;
            return chunk_alloc(bytes, nobjs);
        }
    }

public:
    static void *allocate(size_t bytes) {
        if(bytes > EMaxBytes::MAXBYTES) {
            return malloc(bytes);
        }
        size_t index = FREELIST_INDEX(bytes);
        obj *list = free_list[index];
        if(list) {
            free_list[index] = list->next;
            return list;
        } else {
            return refill(ROUND_UP(bytes));
        }
    }
    static void deallocate(void *ptr, size_t bytes) {
        if(bytes > EMaxBytes::MAXBYTES) {
            free(ptr);
        } else {
            size_t index = FREELIST_INDEX(bytes);
            obj *node = static_cast<obj*>(ptr);
            node->next = free_list[index];
            free_list[index] = node;
        }
    }
    // static void deallocate(void *ptr, unsigned long long);
    static void *reallocate(void *ptr, size_t old_sz, size_t new_sz) {
        deallocate(ptr, old_sz);
        ptr = allocate(new_sz);
        return ptr;
    }
};

char *alloc::start_free = 0;
char *alloc::end_free = 0;
size_t alloc::heap_size = 0;
alloc::obj *alloc::free_list[alloc::ENFreeLists::NFREELISTS] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

}

#endif