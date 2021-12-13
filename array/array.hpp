#ifndef INT_ARRAY
#define INT_ARRAY

#include <initializer_list>

class int_array {
 public:
    explicit int_array(int capacity);
    int_array(const int_array & other);
    int_array(std::initializer_list<int> list);
    int_array(int_array && other);
    ~int_array();
    int_array & operator=(int_array & other);
    int_array & operator=(int_array && other);
    int push_back(int i);
    int at(int i);
    // Removes element from array
    // Assertion error when calling on empty array
    int pop_back();
    int size() const;
    static int_array zero();
 private:
    int * data_;
    int size_ = 0;
    int capacity_;
};

#endif
