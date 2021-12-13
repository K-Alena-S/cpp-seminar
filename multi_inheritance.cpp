#include <iostream>
#include <string>

struct node {
    node(int i) {
        std::cout << i << std::endl;
    }
    node * next() {
        return nullptr;
    }
};

struct node_list {
    node * head;
};

class destructable: public virtual node {
 public:
    destructable(): node(42) {}
    bool should_be_destructed(destructable * d) {
        return true;
    }
    
    std::string name() {
        return "destructable";
    }
};

class moveable: public virtual node {
 public:
    moveable(): node(13) {}
    void move(int x, int y) {
    }

    std::string name() {
        return "moveable";
    }
};

class pacman: public destructable, public moveable {
 public:
    pacman(): node(1) {}
    std::string name() {
        return "pacman";        
    }
};

// class pacman_child: protected pacman {
//  private:
//    void m() {
//        std::cout << i;
//    }
// };

// class pacman_grandchild: public pacman_child {
//  public:
//     void m() {
//         std::cout << i;
//     }
// };

// class pacman: public destructable, public moveable {};

int main(int argc, char const *argv[]) {
    pacman p;
    std::cout << p.name() << std::endl;
    return 0;
}
