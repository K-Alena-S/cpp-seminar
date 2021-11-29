#include "array.hpp"
#include <cassert>
#include <algorithm>
#include <iostream>

int_array::int_array(int capacity) : data_(new int[capacity]), capacity_(capacity) {
    std::cout << "ctor" << std::endl;
}

int_array::~int_array() {
    std::cout << "dtor" << std::endl;
    if (data_ != nullptr) delete[] data_;
}

int int_array::push_back(int i) {
    assert(size_ < capacity_);
    data_[size_] = i;
    size_++;
    return size_;
}

int int_array::at(int i) {
    assert(i < size_ && i >= 0);
    return data_[i];
}

int int_array::pop_back() {
    assert(size_ > 0);
    size_--;
    return data_[size_];
}

int int_array::size() const {
    return size_;
}

int_array & int_array::operator=(int_array other) {
    std::cout << "op=" << std::endl;
    //if (this != &other) {
        //delete[] data_;
        std::swap(data_, other.data_);
        capacity_ = other.capacity_;
        size_ = other.size_;
        //data_ = new int[capacity_];
        //std::copy(other.data_, other.data_ + size_, data_);
    //}
    return *this;
}

int_array::int_array(const int_array & other) : capacity_(other.capacity_),
                                         size_(other.size_),
                                         data_(new int[other.size_]) {
    std::cout << "copyctor" << std::endl;
    std::copy(other.data_, other.data_ + size_, data_);
}

// int_array::stealing_ctor(const int_array & other): capacity_(other.capacity_),
//                                          size_(other.size_), {
//     data_ = other.data_;
//     other.data_ = nullptr;
//     other.size_ = 0;
// }

int_array int_array::zero() {
    static int_array ZERO(0);
    return ZERO;
}

// 1, 11 -> 1, 2, 3, ... 10
// start - inclusive
// end - exclusive
int_array range(int start, int end) {
    assert(end >= start);
    if (end == start) return int_array::zero();
    int_array arr(end - start);
    for (int i = start; i < end; i++) {
        arr.push_back(i);
    }
    return arr;
}

int main(int argc, char const *argv[]) {
    // ctor copyctor dtor dtor
    // int_array arr1;
    // rvalue, lvalue
    // int_array iarr = arr1;
    // some code with arr1
    int_array iarr = range(1, 11);
    // here
    return 0;
}
