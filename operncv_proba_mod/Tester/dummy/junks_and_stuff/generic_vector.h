//
// Created by ghuno on 2022-03-21.
//

#ifndef TESTER_GENERIC_VECTOR_H
#define TESTER_GENERIC_VECTOR_H

///use template to accept anything-> use typeof to get the type -> create generic pointer for first byte -> use type and reinterpret for getting the type back?
///problems: 1) template will make it different -> solution: can create another class which isn't using it
///2) how to store type and use in reinterpretation?

class generic_vector{
public:
    //default (1)
    explicit generic_vector (const allocator_type& alloc = allocator_type());
    //fill (2)
    explicit generic_vector (size_type n, const value_type& val = value_type(),
    const allocator_type& alloc = allocator_type());
    //range (3)
    template <class InputIterator> generic_vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
    //copy (4)
    generic_vector (const vector& x);
};

#endif //TESTER_GENERIC_VECTOR_H
