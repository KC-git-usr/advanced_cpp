#include <iostream>
#include <variant>
#include <vector>

// CRTP
template<typename DerivedAnimal>
class Animal {
public:
    void MakeNoise() {
        static_cast<DerivedAnimal*>(this)->MakeNoise();
    }
};

class Dog: public Animal<Dog> {
    public:
    static void MakeNoise() {
        std::cout<<"Woof!"<<std::endl;
    }
};

class Cat: public Animal<Cat> {
    public:
    static void MakeNoise() {
        std::cout<<"Meow!"<<std::endl;
    }
};

template<typename DerivedAnimal>
void PerformAction(Animal<DerivedAnimal>& animal) {
    animal.MakeNoise();
}

int main(int argc, char** argv) {
    // CRTP START
    Dog dog;
    Cat cat;
    PerformAction(dog);
    PerformAction(cat);

    std::vector<std::variant<Dog, Cat>> animals;
    animals.emplace_back(dog);
    animals.emplace_back(cat);
    for (auto& animal : animals) {
        std::visit([](auto& a) { a.MakeNoise(); }, animal);
    }
    // CRTP END

    return 0;
}
