#include "array.hpp"
#include <cassert>
#include <iostream>
#include <algorithm>

int_array::int_array(int capacity) : data_(new int[capacity]), capacity_(capacity) {}

int_array::~int_array() {
    delete[] data_;
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

int_array::int_array(int_array & other) : capacity_(other.capacity_),
                                         size_(other.size_),
                                         data_(new int[other.size_]) {
    std::copy(other.data_, other.data_ + size_, data_);
}

int main(int argc, char const * argv[]) {
    int_array arr(10);
    arr.push_back(13);
    arr.push_back(42);
    // 13
    std::cout << arr.at(0) << std::endl;
    // 42
    std::cout << arr.pop_back() << std::endl;
    // 1
    std::cout << "Size: " << arr.size() << std::endl;
    int_array arr2(4);
    arr2 = arr;
    // 13
    std::cout << "First element: " << arr2.at(0) << std::endl;
    return 0;
}
