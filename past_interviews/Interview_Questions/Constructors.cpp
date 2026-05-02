//
// Created by Kumar Chakravarthy on 22-Apr-23.
//

#include <iostream>
#include <string>

class Foo {

    int x_;
    std::string* s_;

public:

    Foo(int x = 0, std::string s = "") : x_(x) {
        this->s_ = new std::string(s);
        std::cout << "Parameterized constructor called" << std::endl;
    }

    Foo(const Foo& rhs) {
        this->x_ = rhs.x_;
        this->s_ = new std::string(*rhs.s_);
        std::cout << "Copy constructor called" << std::endl;
    }

    Foo& operator=(const Foo& rhs) {
        if(this == &rhs)
            return *this;
        this->x_ = rhs.x_;
        this->s_ = new std::string(*rhs.s_);
        std::cout << "Assignment constructor called" << std::endl;
        return *this;
    }

    Foo(Foo&& input) : x_(std::move(input.x_)), s_(std::move(input.s_)) {
        input.x_ = 0;
        input.s_ = nullptr;
        delete input.s_;
        std::cout << "Move constructor called" << std::endl;
    }

    ~Foo() {
        delete this->s_;
        std::cout << "Destructor called" << std::endl;
    }

    friend std::ostream& operator<<(std::ostream& os, const Foo& input) {
        os << input.x_ << ", " << *input.s_;
        return os;
    }
};

Foo getObject() {
    return Foo(12, "Ashwin");
}

int main() {
//    // Call parameterized constructor
//    std::cout << "Creating obj_1" << std::endl;
//    Foo obj_1(25, "Kumar");
//
//    // Call copy constructor
//    std::cout << "Creating obj_2" << std::endl;
//    Foo obj_2(obj_1);
//
//    // Call assignment constructor
//    std::cout << "Creating obj_3" << std::endl;
//    Foo obj_3;
//    obj_3 = obj_1;
//
//    // Call move constructor using existing object
//    std::cout << "Creating obj_4" << std::endl;
//    Foo obj_4(std::move(obj_1));

    // Call move constructor using temp object
    std::cout << "Creating obj_5" << std::endl;
    Foo obj_5(getObject());

//    std::cout << obj_1 << std::endl;
//    std::cout << obj_2 << std::endl;
//    std::cout << obj_3 << std::endl;
//    std::cout << obj_4 << std::endl;
    std::cout << obj_5 << std::endl;
}