#include "library.h"
#include <cstdlib>
#include <stdexcept>

const unsigned int DEFAULT_VEC_LENGTH = 8;

template <typename T> int Vec<T>::len() {
    return this->length;
}

// default constructor
template<typename T>
Vec<T>::Vec() {
    this->ptr = new T[DEFAULT_VEC_LENGTH];
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
void Vec<T>::push_back(T next_elm) {
    unsigned int len = this->length;
    if(len == this->capacity) {
        // Set a new capacity, create a new array, copy values from the old array to the new one, delete the old array,
        // re-set the ptr to our new array
        this->capacity *= 2;
        T* new_arr = new T[this->capacity];
        for(unsigned int i = 0; i < len; i++) {
            new_arr[i] = this->ptr[i];
        }
        delete [] this->ptr;
        this->ptr = new_arr;
    }
    this->ptr[len] = next_elm;
    this->length += 1;
}

template<typename T>
void Vec<T>::pop_back() {
    unsigned int len = this->length;
    if(len > 0) {
        // Here I can use either `delete this->ptr[len]` or `this->ptr[len].~T()`
        // The first would release memory, which we do not want. We want to destruct the final element,
        // but we do not want to free the memory. The memory is still owned by the vector until this->capacity.
        this->ptr[len - 1].~T();
        this->length -= 1;
    }
}

template<typename T>
void Vec<T>::push_front(T new_elm) {
    this->_insert_element(new_elm, 0);
}

template<typename T>
void Vec<T>::pop_front() {
    this->_remove_element(0);
}

template<typename T>
void Vec<T>::insert(T new_elm, unsigned int position) {
    this->_insert_element(new_elm, position);
}

template<typename T>
void Vec<T>::remove(unsigned int position) {
    this->_remove_element(position);
}

template<typename T>
void Vec<T>::_insert_element(T new_elm, unsigned int position) {
    if(position > this->length) {
        throw std::runtime_error("Tried to insert at an invalid vector index.");
    }
    if(this->length == this->capacity) {
        // We are at capacity, so we are going to double it before initializing a new array
        this->capacity *= 2;
    }
    T* new_arr = new T[this->capacity];

    // This can be done with branching and a variable to keep track of whether the new element has been inserted
    // but branching is slower
    for(unsigned int i = 0; i < position; i++) {
        new_arr[i] = this->ptr[i];
    }
    new_arr[position] = new_elm;
    for(unsigned int i = position + 1; i < this->length + 1; i++) {
        new_arr[i] = this->ptr[i - 1];
    }
    this->length += 1;
    delete [] this->ptr;
    this->ptr = new_arr;
}

template<typename T>
void Vec<T>::_remove_element(unsigned int position) {
    if(position >= this->length) {
        throw std::runtime_error("Tried to remove at an invalid vector index.");
    }
    T* new_arr = new T[this->capacity];
    for(unsigned int i = 0; i < position; i++) {
        new_arr[i] = this->ptr[i];
    }
    for(unsigned int i = position + 1; i <= this->length; i++) {
        new_arr[i - 1] = this->ptr[i];
    }
    this->length -= 1;
    delete [] this->ptr;
    this->ptr = new_arr;
}
