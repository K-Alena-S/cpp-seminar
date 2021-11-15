#include <iostream>
#include <memory>

class A {
 public:
    A(int i = 0): _i(i) { std::cout << "ctor" << std::endl; }
    ~A() {std::cout << "dtor" << std::endl; }
    void inc() { _i++; std::cout << "inc" << std::endl; }
 private:
    int _i;
};

template<typename T, typename TDeleter>
class my_unique_ptr {
 public:
    my_unique_ptr(T * ptr, TDeleter deleter): _ptr(ptr), _deleter(deleter) {}
    ~my_unique_ptr() { if (_ptr != nullptr) _deleter(_ptr); }
    T & operator*() { return *_ptr; }
    T * operator->() { return _ptr; }
    T * release() {
        T * cur = _ptr;
        _ptr = nullptr;
        return cur;
    }
    void reset(T * new_ptr) {
        T * cur = _ptr;
        _ptr = new_ptr;
        if (cur != nullptr) _deleter(cur);
    }
 private:
    my_unique_ptr(my_unique_ptr & other) = delete;
    my_unique_ptr & operator=(my_unique_ptr &) = delete;
    T * _ptr;
    TDeleter _deleter;
};

// template<typename T>
// class my_unique_ptr<T[]> {

// };

template<typename T>
class Box {
 public:
    Box(T value): _value(value) {}
    void print() {
        std::cout << _value << std::endl;
    }
 private:
    T _value;
};

template<>
class Box<int> {
public:
    Box(int value) {}
    void print() {
        std::cout << "no value" << std::endl;
    }
};

class ADeleter {
 public:
    void operator()(A * a) { 
        std::cout << "a deleter" << std::endl;
        delete a;
    }
};

void test(bool b) {
    Box<int>(42);
    Box<double>(42.0);
    // my_unique_ptr_A
    //  my_unique_ptr<A> ptr1 = my_unique_ptr<A>(new A());
    // delete ptr1.release();
    A * a1 = new A();
    // my_unique_ptr<A> ptr1 = my_unique_ptr<A>(a1);
    // A * a2 = new A[100]();

    my_unique_ptr<A, ADeleter> ptr = my_unique_ptr<A, ADeleter>(a1, ADeleter());
    
    //  (*ptr).inc();
    //  ptr->inc();
     

    // ptr++;
    //  ptr++;
    //  ptr--;

    // 1. dereference with *
    // 2. pointer arithmetic
    // 3. ->
    // A * a = new A();
    // a->inc();
    // (*a).inc();
    
    // some other code
    // 1. double free (delete a)
    // 2. if (b) return;
    // 3. some exception
}

int main(int argc, char const *argv[]) {
    test(true);
    return 0;
}

