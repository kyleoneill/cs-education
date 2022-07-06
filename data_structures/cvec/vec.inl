#include "library.h"
#include <cstdlib>
#include <stdexcept>

const unsigned int DEFAULT_VEC_LENGTH = 8;

template <typename T> int Vec<T>::len() {
    return this->length;
}

/*
 * This template used to use `new T[some_len]` and now uses malloc. malloc is preferred as it returns
 * a pointer to a chunk of memory without initializing it, whereas the `new` keyword initializes the memory space
 * that it returns. We do not want this overhead, especially for the cases where T might be some heavy/complicated
 * struct and running that initialization on a large vector will introduce a lot of overhead operations. This way we
 * only initialize what we use.
 *
 * After removing `new`, we have to also remove `delete`. Delete calls the destructor for a type before freeing its
 * memory, so we need to call the destructor ourselves.
 *
 * The functions that add values take `const T&` rather than `T` for the scenario where `T` is a type that is non-trivially
 * copy-able. When non-trivially copy-able data, like a string, is passed as just `T` the compiler will make a copy
 * of that data and give the copy to this function. Using `const T&` will prevent the compiler from making a copy. We
 * are making our own copy so we want to avoid the overhead of doing it twice.
 */

// default constructor
template<typename T>
Vec<T>::Vec() {
    // this->ptr = new T[DEFAULT_VEC_LENGTH];
    this->ptr = this->_malloc_vector(DEFAULT_VEC_LENGTH);
    this->length = 0;
    this->capacity = DEFAULT_VEC_LENGTH;
}

template<typename T>
T Vec<T>::operator[](unsigned int i) {
    if(i < this->length) {
        return this->ptr[i];
    }
    else {
        throw std::runtime_error("Tried to index vector by an out of range value.");
    }
}

template<typename T>
Vec<T>& Vec<T>::operator=(T new_value) {

}

template<typename T>
void Vec<T>::push_back(const T& next_elm) {
    unsigned int len = this->length;
    if(len == this->capacity) {
        // Set a new capacity, create a new array, copy values from the old array to the new one, delete the old array,
        // re-set the ptr to our new array
        this->capacity *= 2;
        T* new_arr = this->_malloc_vector(this->capacity);
        for(unsigned int i = 0; i < len; i++) {
            this->_assign_at_index(new_arr, i,  this->ptr[i]);
        }
        this->_call_destructors_and_free();
        this->ptr = new_arr;
    }
    this->_assign_at_index(this->ptr, len,  next_elm);
    this->length += 1;
}

template<typename T>
void Vec<T>::pop_back() {
    unsigned int len = this->length;
    if(len > 0) {
        // Here we call the destructor for a type to clear this block in the array. We want to destruct values
        // that we remove, but do not want to free that memory as it is still owned by this->ptr
        this->ptr[len - 1].~T();
        this->length -= 1;
    }
}

template<typename T>
void Vec<T>::push_front(const T& new_elm) {
    this->_insert_element(new_elm, 0);
}

template<typename T>
void Vec<T>::pop_front() {
    this->_remove_element(0);
}

template<typename T>
void Vec<T>::insert(const T& new_elm, unsigned int position) {
    this->_insert_element(new_elm, position);
}

template<typename T>
void Vec<T>::remove(unsigned int position) {
    this->_remove_element(position);
}

template<typename T>
void Vec<T>::_insert_element(const T& new_elm, unsigned int position) {
    if(position > this->length) {
        throw std::runtime_error("Tried to insert at an invalid vector index.");
    }
    if(this->length == this->capacity) {
        // We are at capacity, so we are going to double it before initializing a new array
        this->capacity *= 2;
    }
    T* new_arr = this->_malloc_vector(this->capacity);

    // This can be done with branching and a variable to keep track of whether the new element has been inserted
    // but branching is slower
    for(unsigned int i = 0; i < position; i++) {
        this->_assign_at_index(new_arr, i,  this->ptr[i]);
    }
    this->_assign_at_index(new_arr, position,  new_elm);
    for(unsigned int i = position + 1; i < this->length + 1; i++) {
        this->_assign_at_index(new_arr, i,  this->ptr[i - 1]);
    }
    this->length += 1;
    this->_call_destructors_and_free();
    this->ptr = new_arr;
}

template<typename T>
void Vec<T>::_remove_element(unsigned int position) {
    if(position >= this->length) {
        throw std::runtime_error("Tried to remove at an invalid vector index.");
    }
    T* new_arr = this->_malloc_vector(this->capacity);
    for(unsigned int i = 0; i < position; i++) {
        this->_assign_at_index(new_arr, i,  this->ptr[i]);
    }
    for(unsigned int i = position + 1; i <= this->length; i++) {
        this->_assign_at_index(new_arr, i - 1,  this->ptr[i]);
    }
    this->length -= 1;
    this->_call_destructors_and_free();
    this->ptr = new_arr;
}

template<typename T>
T* Vec<T>::_malloc_vector(unsigned int size) {
    return (T*) malloc(size * sizeof(T));
}

template<typename T>
void Vec<T>::_call_destructors_and_free() {
    // Destruct our data before freeing it
    for(unsigned int i = 0; i < this->length; i++) {
        this->ptr[i].~T();
    }
    free(this->ptr);
}

template<typename T>
void Vec<T>::_assign_at_index(T* arr, unsigned int index, const T& new_val) {
    new (arr + index) T(new_val);
}
