class int_array {
 public:
    explicit int_array(int capacity);
    int_array(int_array & other);
    ~int_array();
    int_array & operator=(int_array & other);
    int push_back(int i);
    int at(int i);
    int pop_back();
    int size() const;
 private:
    int * data_;
    int size_ = 0;
    int capacity_;
};