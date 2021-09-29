#include <iostream>
#include "array.hpp"

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
    std::cout << "Hello" << std::endl;
    return 0;
}