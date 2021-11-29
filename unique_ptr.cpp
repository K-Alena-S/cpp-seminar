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
class base_my_unique_ptr {
 public:
    base_my_unique_ptr(T * ptr, TDeleter deleter): _ptr(ptr), _deleter(deleter) {}
    ~base_my_unique_ptr() { if (_ptr != nullptr) _deleter(_ptr); }
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
    base_my_unique_ptr(base_my_unique_ptr & other) = delete;
    base_my_unique_ptr & operator=(base_my_unique_ptr &) = delete;
    T * _ptr;
    TDeleter _deleter;
};

template<typename T>
class default_deleter {
 public:
    void operator()(T * t) {
        delete t;
    }
};

template<typename T>
class array_deleter {
 public:
    void operator()(T * t) {
        delete[] t;
    }
};

// 1. T
// 2. T + TDeleter
template<typename T, typename TDeleter=default_deleter<T>>
class my_unique_ptr: public base_my_unique_ptr<T, TDeleter> {
 public:
    my_unique_ptr(T * t, TDeleter deleter=TDeleter()): base_my_unique_ptr<T, TDeleter>(t, deleter) {}
};

// 3. T[]
template<typename T>
class my_unique_ptr<T[]>: public base_my_unique_ptr<T, array_deleter<T>> {
 public:
    my_unique_ptr(T * t): base_my_unique_ptr<T, array_deleter<T>>(t, array_deleter<T>()) {}
};

// 4. T[] + TDeleter
template<typename T, typename TDeleter>
class my_unique_ptr<T[], TDeleter>: public base_my_unique_ptr<T, TDeleter> {
 public:
    my_unique_ptr(T * t, TDeleter deleter=TDeleter()): base_my_unique_ptr<T, TDeleter>(t, deleter) {}
};

template<typename T>
my_unique_ptr<T, default_deleter<T>> make_my_unique() {
    return my_unique_ptr(new T(), default_deleter<T>());
}

void test(bool b) {
    // my_unique_ptr_A
    //  my_unique_ptr<A> ptr1 = my_unique_ptr<A>(new A());
    // delete ptr1.release();
    A * a1 = new A();
    // my_unique_ptr<A> ptr1 = my_unique_ptr<A>(a1);
    // A * a2 = new A[100]();


    // 1. type + custom deleter
    // std::unique_ptr<A, default_deleter<A>> sptr1(new A(), default_deleter<A>());
    my_unique_ptr<A, default_deleter<A>> ptr1(new A(), default_deleter<A>());
    // 2. type
    // std::unique_ptr<A> sptr2(new A());
    my_unique_ptr<A> ptr2(new A());
    // // 3. array type
    // std::unique_ptr<A[]> sptr2(new A[1]());
    A * a_arr = new A[1]();
    my_unique_ptr<A[]> ptr3(a_arr);
    // // 4. array type + custom deleter
    // std::unique_ptr<A[], default_deleter<A>> sptr2(new A[1](), default_deleter<A>());
    my_unique_ptr<A[], array_deleter<A>> ptr4(new A[1](), array_deleter<A>());
    
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

