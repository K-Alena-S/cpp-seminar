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

template<typename T>
class BaseBox {
 public:
    BaseBox(T t) {
    }
    void foo() {}
};

template<typename T>
class Box {
 public:
    Box(T t) {}
};

template<>
class Box<int>: public BaseBox<int> {
 public:
    Box(int i): BaseBox<int>(i) {}
};

template<typename T>
class Box<T[]>: public BaseBox<T[]> {
 public:
    Box(T t[]): BaseBox<T[]>(t) {}
};

void testBox() {
    int i[] = {1, 2, 3};
    int ii = 42;
    Box<int[]> b1(i);
    b1.foo();
    Box<int> b2(ii);
    b2.foo();
    Box<double> b3(41.0);
}

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

bool foo() {
    // may throw exception
    return true;
}

void bar(std::unique_ptr<A> a, bool b) {}

template<typename T>
my_unique_ptr<T, default_deleter<T>> make_my_unique() {
    return my_unique_ptr(new T(), default_deleter<T>());
}

void callBar() {
    bar(std::make_unique<A>(), foo());
}

void test(bool b) {
    // my_unique_ptr_A
    //  my_unique_ptr<A> ptr1 = my_unique_ptr<A>(new A());
    // delete ptr1.release();
    A * a1 = new A();
    // my_unique_ptr<A> ptr1 = my_unique_ptr<A>(a1);
    // A * a2 = new A[100]();


    // 1. type + custom deleter
    std::unique_ptr<A, default_deleter<A>> sptr1(new A(), default_deleter<A>());
    my_unique_ptr<A, default_deleter<A>> ptr1(new A(), default_deleter<A>());
    // 2. type
    std::unique_ptr<A> sptr2(new A());
    // my_unique_ptr<A> ptr2(new A());
    // // 3. array type
    // std::unique_ptr<A[]> sptr2(new A[1]());
    // my_unique_ptr<A[]> ptr3(new A[1]());
    // // 4. array type + custom deleter
    // std::unique_ptr<A[], default_deleter<A>> sptr2(new A[1](), default_deleter<A>());
    // my_unique_ptr<A[], default_deleter<A>> ptr4(new A[1](), default_deleter<A>());
    
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

