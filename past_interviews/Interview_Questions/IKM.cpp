//
// Created by Kumar Chakravarthy on 15-Apr-23.
//

#include <iostream>
#include <bits/stdc++.h>


// mutable keyword start
class X
{
public:
    bool GetFlag() const {
        m_accessCount++;
        return m_flag;
    }
private:
    bool m_flag;
    mutable int m_accessCount;
};
// mutable keyword end


// const keyword start
class Y {
public:
    const int kSize;

    Y() :
    kSize(10){
    }
};


class Z: public Y {
public:
    void Print() {
        std::cout << "kSize : " <<this->kSize<<std::endl;
    }
};
// const keyword end


// this keyword start
/*
 * If you had a function that returned this, it would be a pointer to the
 * current object, while a function that returned *this would be
 * a "clone" of the current object, allocated on the stack -- unless you have
 * specified the return type of the method to return a reference.*/
class Foo {
public:
    Foo() {
        this->value = 0;
        std::cout << "New object was created" << std::endl;
    }

    Foo get_copy() {
        std::cout << "get_copy called" << std::endl;
        return *this;
    }

    Foo& get_copy_as_reference() {
        std::cout << "get_copy_as_reference called" << std::endl;
        return *this;
    }

    Foo* get_pointer() {
        std::cout << "get_pointer called" << std::endl;
        return this;
    }

    void increment() {
        std::cout << "increment called" << std::endl;
        this->value++;
    }

    void print_value() {
        std::cout << this->value << std::endl;
    }

private:
    int value;
};
// this keyword end


// typeid keyword start
class Base {
public:
    virtual void vvfunc() {}
};

class Derived : public Base {};
// typeid keyword end


// enum start
class Fruit {
public:
    int weight;
    char season;
};

class Apple : public Fruit {
public:
    enum variety{ Gala, Fuji, Granny};
    void setVariety(variety v) {
        type = v;
    }
private:
    variety type;
};

class Orange : Fruit {
    enum use{Eating, Juice};
public:
    using Fruit::season;
    use type;
};
// enum end


// lvalue vs rvalue start
std::string getCity(bool c) {
    return (c ? "Chicago" : "New York");
}

void printCity(const std::string& city) {
    std::cout << "Implementation 1 called" << std::endl;
}

void printCity(std::string&& city) {
    std::cout << "Implementation 2 called" << std::endl;
}
// lvalue vs rvalue end


// for_each start
struct Increment {
    // Note : return type is void
    void operator()(int& input) {
        input *= 2;
    }
}functor_obj;

// Note : return type is void
// and the input type is the type of the de-referenced iterator
void multiplier(int& input) {
    input *= 2;
}
// for_each end


// pure virtual function start
class Class_Foo {
public:
    Class_Foo() {
        std::cout << "Called Class Foo ctor" << std::endl;
    }

    // To make it a pure virtual func, it has to be assigned to 0
    virtual void my_virtual_func() = 0;

    virtual ~Class_Foo() {}
};

class Class_Bar : public Class_Foo{
public:
    Class_Bar() {
        std::cout << "Called Class Bar ctor" << std::endl;
    }

    void my_virtual_func() override {
        std::cout << "Called my_virtual_func from base class" << std::endl;
    }

    virtual ~Class_Bar() {}
};
// pure virtual function end



int main() {
    std::cout<<"Hello from main"<<std::endl;

    // mutable keyword
    if(false) {
        int i = 7;
        char code = 'a';

        [=, &i]() mutable {
            i++;
            code = 'b';
            std::cout << "i : " << i << "code : " << code << std::endl;
        }();

        std::cout<<"i : "<<i<<"code : "<<code<<std::endl;
    }


    // const data members
    if(false) {
        Z *z = new Z;
        z->Print();
        std::vector<Z*> my_vector;
        my_vector.push_back(z);
    }

    // this keyword
    if(false) {
        Foo foo;
        foo.increment();
        foo.print_value(); // 1

        foo.get_copy().increment();
        foo.print_value(); // 1

        // the call stack is from left to right
        foo.get_copy_as_reference().increment();
        foo.print_value(); // 2

        foo.get_pointer()->increment();
        foo.print_value(); // 3
    }

    // typeid keyword
    if(false) {
        Derived* pd = new Derived;
        Base* pb = pd;
        std::cout << typeid( pb ).name() << std::endl;   //prints "class Base *"
        std::cout << typeid( *pb ).name() << std::endl;   //prints "class Derived"
        std::cout << typeid( pd ).name() << std::endl;   //prints "class Derived *"
        std::cout << typeid( *pd ).name() << std::endl;   //prints "class Derived"
        delete pd;
        pb = nullptr;
    }

    // enum keyword
    if(false) {
        Orange f1;
        Apple f2;
        f2.weight = 14;
        f1.season = 'S';
        f2.setVariety(Apple::Fuji);
        f2.setVariety(Apple::variety::Gala);
    }

    // lvalue vs rvalue
    if(false) {
        std::string my_city = getCity(false);
        printCity(my_city);
        printCity(std::move(my_city));
        printCity(getCity(true));
    }

    // for_each
    if(false) {
        std::vector<int> my_vec {1, 2, 3, 4};
        // functor, note we are passing the object
        std::for_each(my_vec.begin(), my_vec.end(), functor_obj);  // passing the functor obj
        std::for_each(my_vec.begin(), my_vec.end(), Increment());  // passing a temp functor obj
        for(const int& x : my_vec)
            std::cout << x << " ";
        std::cout << std::endl;
        // function
        std::for_each(my_vec.begin(), my_vec.end(), multiplier);
        for(const int& x : my_vec)
            std::cout << x << " ";
        std::cout << std::endl;
    }

    // virtual function
    if(false) {
        //  Class_Foo obj_foo;  // invalid
        Class_Bar obj_bar;
        obj_bar.my_virtual_func();
    }

}
