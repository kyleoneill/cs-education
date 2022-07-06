#ifndef CVEC_LIBRARY_H
#define CVEC_LIBRARY_H

void hello();

#ifndef CVEC_H
#define CVEC_H

template <typename T> class Vec {
private:
    T* ptr;
    unsigned int length;
    unsigned int capacity;
    void _insert_element(const T& new_elm, unsigned int position);
    void _remove_element(unsigned int position);
    T* _malloc_vector(unsigned int size);
    void _call_destructors_and_free();
    void _assign_at_index(T* arr, unsigned int index, const T& new_val);
public:
    int len();
    Vec();
    T operator[](unsigned int i);
    Vec<T>& operator=(T new_value);
    void push_back(const T& next_elm);
    void pop_back();
    void push_front(const T& new_elm);
    void pop_front();
    void insert(const T& new_elm, unsigned int position);
    void remove(unsigned int position);
};
#include "vec.inl"

#endif // CVEC_H

#endif //CVEC_LIBRARY_H
