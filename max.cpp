#include <iostream>

template<class T>
T * max(T * start, T * end) {
    // class MyGt {
    //     MyGt(T *& start, T *& end, MyGt & gt, MyInt & myInt) {}
    //     public:
    //     bool operator()(T & a, T & b) const {
    //         return a > b;
    //     }
    // };
    //const MyGt & gt = MyGt();
    return max(start, end, [](T & a, T & b) { return *a > *b; });
}

template<class T, class Gt>
T * max(T * start, T * end, const Gt & gt) {
    T * max = start;
    for (T * cur = start; cur < end; cur++) {
        if (gt(*cur, *max)) *max = *cur;
    }
    return max;
}

// class IntGt {
//     public:
//     bool operator()(int i1, int i2) const {
//         return i1 > i2;
//     }
// };

// template<class T>
// T * max(T * start, T * end, bool (* gt)(T & t1, T & t2)) {
//     T * max = start;
//     for (T * cur = start; cur < end; cur++) {
//         if (gt(*cur, *max)) *max = *cur;
//     }
//     return max;
// }

class MyInt {
 public:
    MyInt(int i): i_(i) {}
    bool operator>(MyInt & other) {
        return i_ > other.i_;
    }
    void print() {
        std::cout << i_ << std::endl;
    }
 private:
    int i_;
};

// bool int_gt(int i1, int i2) {
//     return i1 > i2;
// }

int main(int argc, char const *argv[]) {
    int a[] = {1, 3, 2};
    // 3
    std::cout << *max(a, a + 3, [](int a, int b) { return a > b;}) << std::endl;
    // double d[] = {1.45, 1.46, 1.44};
    // std::cout << *max(d, d + 3) << std::endl;
    // MyInt mi[]= {MyInt(3), MyInt(4), MyInt(1)};
    // max(mi, mi + 3)->print();
    return 0;
}
