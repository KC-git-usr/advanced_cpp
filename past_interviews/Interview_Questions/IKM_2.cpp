//
// Created by Kumar Chakravarthy on 07-May-23.
//
#include <iostream>
#include <string>


// ctor start
class MaS {
public:
    MaS(std::string s = "", int i = 10) {}

    MaS(MaS const & rhs) {
        std::cout << "Called ctor 2" << std::endl;
    }

    MaS(MaS& rhs) {
        std::cout << "Called ctor 1" << std::endl;
    }

    MaS(MaS && rhs) {
        std::cout << "Called ctor 3" << std::endl;
    }
};
// ctor end

// const start
class Adjustor {
public:
    Adjustor() {}
    void testAdjustor() {
        std::cout << "test and adjust" << std::endl;
    }
    void testAdjustor() const {
        std::cout << "test only" << std::endl;
    }
};

void testAdj(const Adjustor& adj) {
    adj.testAdjustor();
}
// const end


// casting start
class Dwelling {
public:
    char day;
};

class House : public Dwelling{
public:
    enum roofStyle {flat, gable, hip};
};

class MultiUnit : public  Dwelling {
public:
    int numUnits;
};
// casting end


// virtual functions start
class Base {
public:
    virtual void print() {
        std::cout << "base" << std::endl;
    }
};

class Derived :public Base{
public:
    void print() {
        std::cout << "derived" << std::endl;
    }
};
// virtual functions end



int main() {

    // ctor
    if(false) {
        MaS mas1("Kumar", 10);
        MaS mas2(mas1);  // why does this call ctor 1 and not ctor 2 ?
        MaS mas3 = std::move(mas1);
        MaS mas4(MaS("Harold", 20));  // why isn't this calling ctor 3? because of copy elision
    }

    // const onj and members
    if(false) {
        const Adjustor monitor;
        Adjustor moderator;
        Adjustor* const pAdj = &moderator;

        pAdj->testAdjustor();
        testAdj(moderator);
        testAdj(monitor);
        moderator.testAdjustor();
        monitor.testAdjustor();
    }

    // casting
    if(false) {
        Dwelling hut;
        House home;
        MultiUnit building;

        Dwelling myResidence = home;
    }

    if(true) {
        // Upcasting
        Derived d;
        d.print();  // derived
        Base *pBase_1 = new Base();
        Base *pBase_2 = &d;
        pBase_1->print();  // base
        pBase_2->print();  // derived, we can't look down, only look up, which func to call will be
                            // gotten from vtable and the type of the obj the ptr is pointing to is
                            // calling it

        // Downcasting
        Derived *pDerived;
        Base *b = new Base();
        pDerived = (Derived*)b;
        pDerived->print();  // base
    }
}