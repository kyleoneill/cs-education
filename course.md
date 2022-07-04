# CS Course

## Introduction
1. Command line debugging
2. Learn a build system, like CMake or Ninja
3. Make a simple algorithmic program, convert a string representation of roman numerals into an int

## Data Structures

### Dynamic Arrays
A dynamic array is defined by
1. Access by index
2. Push/pop to add and take away from the end
    - Can also have push_front, pop_front
3. Insert to add data at some arbitrary index

There are four common implementations of dynamic arrays; linked-lists, vectors, deques, and queues.

A bike and a car are both vehicle data structures. A bike is preferable if you care about gas, a car is preferable if you care about speed. We choose a class of data structure to support a specific need.

### Vector
A vector is an implmentation of a dynamic array and the most used data structure.

What makes a vector unique? Vectors provide random access, so it is always the same price to access an element no matter where it is in the array.

| Operation  | O-Notation         |
| ---------  | ----------         |
| Lookup     | constant           |
| push_back  | amortized constant |
| pop_back   | constant           |
| push_front | linear             |
| pop_front  | linear             |
| insert     | linear             |
| remove     | linear             |

Internally a vector is composed of three parts.
1. pointer
    - To some block of memory that has room for `{capacity}` elements
2. length
    - The number of elements that are currently contained
    - Everything left is unused space
3. capacity

When you push_back, it checks if it has spare capacity. If it does, inc the length and insert to the end.
When length and capacity are equal, you must re-allocate:
1. Choose a new larger capacity according to some rule
    - The most common rule is to double capacity
2. Allocate space according to that limit
3. Move all of the existing elements to our new space
4. Free the old memory
5. Replace the pointer/capacity with our new values
6. Perform the normal operation

Why is push_back "amortized constant"? It means that on average an operation will be constant. The operations that involve re-allocating space to re-size the vector will take linear time, but the number of times you perform those operations will inverse exponential (or, logarithmic) because every time you perform that operation your size doubles. This means that the vector size increases exponentially, the number of times you need to increase it is logarithmic.

Homework
1. Implement the vector type
    - Also add some special functionality that vectors can have
        1. Reserve - increase the capacity by a requested amount
        2. Pop - return the last element to you and remove it from the vector
            - make sure the memory is managed correctly here. Will likely have to copy the 
              last element to a new variable?