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
    void _insert_element(T new_elm, unsigned int position);
    void _remove_element(unsigned int position);
public:
    int len();
    Vec();
    T operator[](unsigned int i);
    void push_back(T next_elm);
    void pop_back();
    void push_front(T new_elm);
    void pop_front();
    void insert(T new_elm, unsigned int position);
    void remove(unsigned int position);
};
#include "vec.inl"

#endif // CVEC_H

#endif //CVEC_LIBRARY_H
