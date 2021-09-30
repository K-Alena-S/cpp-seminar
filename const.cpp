#include <iostream>

// 1

void test1() {
    const int i = 42;
    std::cout << "i = " << i << std::endl;      // OK
    i = 53;                                     // Error: write to const variable
}

// 2

class Box {
public:
 const int i = 0;
};

void test2() {
    Box box;
    std::cout << "i = " << box.i << std::endl;  // OK
    box.i = 42;                                 // Error: write to const variable
}

// 3

class BoxWithGetSet {
 public:
  void setI(int i) {
      i_ = i;                                   // Error: write to const variable
  }

  int getI() {
      return i_;                                // OK
  }
 private:
  const int i_;
};

// 4. how to mark some methods as "changes i" and some as "leaves i as is"?

class BoxWithGetSetThatWorks {
public:
  void setI(int i) {
      i_ = i;                                   // OK
  }

  int getI() const {
      return i_;                                // OK
  }
private:
  int i_;
};

// 5

class BoxWithCalls {
 public:
   void foo() const {
       bar();                                   // Error: can call only const methods from const method
       baz();                                   // OK
   }

   void bar() {
   }
   void baz() const {}
private:
   int i_;
};

// 6. this two functions 'printI' do the same thing: they mark Box instance as const
// if object is const then all of its fields are considered as const
class Box {
 public:
   friend void printI(const Box * box);
   void printI() const { std::cout << this->i_ << std::endl; }
 private:
    int i_;
};

void printI(const Box * box) {
    std::cout << box->i_ << std::endl;
    box->i_++;                                  // Error: box is const so i_ is also const
}

int main(int argc, char const *argv[]) {
    return 0;
}