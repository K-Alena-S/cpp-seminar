#include "array.hpp"
#include <cassert>
#include <iostream>

int_array::int_array(int capacity): data_(new int[capacity]), capacity_(capacity) {}

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

int int_array::size() {
    return size_;
}

int main(int argc, char const *argv[]) {
    int_array arr(10);
    arr.push_back(13);
    arr.push_back(42);
    // 13
    std::cout << arr.at(0) << std::endl;
    // 42
    std::cout << arr.pop_back() << std::endl;
    // 1
    std::cout << "Size: " << arr.size() << std::endl;
    return 0;
}
