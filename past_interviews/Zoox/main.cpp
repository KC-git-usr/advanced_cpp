#include <cstdint>
#include <iostream>
#include <queue>
#include <ranges>
#include <unordered_map>
#include <variant>
#include <vector>

// CRTP START
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
// CRTP END

// umap with custom hashable Key START
struct Key {
    int id;
    std::string name;

    bool operator==(const Key& rhs) const {
        return id == rhs.id && name == rhs.name;
    }
};

struct CustomKeyHash {
    std::size_t operator()(const Key& key) const {
        const std::size_t h1 = std::hash<int>{}(key.id);
        const std::size_t h2 = std::hash<std::string>{}(key.name);
        return h1 ^ (h2 << 1);
    }
};
// umap with custom hashable Key END

// Rule of 5 START
class DynamicArray {
public:
    explicit DynamicArray(const size_t arr_size) : arr_size(arr_size), data(new uint8_t[arr_size]()) {
        std::cout<<"Explicit c'tor\n";
    }

    DynamicArray(const DynamicArray& rhs) : arr_size(rhs.arr_size), data(new uint8_t[arr_size]) {
        std::cout<<"Copy c'tor\n";
        for (size_t i = 0; i < arr_size; ++i) {
            data[i] = rhs.data[i];
        }
    }

    DynamicArray& operator=(const DynamicArray& rhs) {
        std::cout<<"Copy assignment c'tor\n";
        if (this != &rhs) {
            auto* const tmp = new uint8_t[rhs.arr_size];
            for (size_t i = 0; i < rhs.arr_size; ++i) {
                tmp[i] = rhs.data[i];
            }
            this->arr_size = rhs.arr_size;
            delete[] this->data;
            this->data = tmp;
        }
        return *this;
    }

    DynamicArray(DynamicArray&& input) noexcept : arr_size(input.arr_size), data(input.data) {
        std::cout<<"Move c'tor\n";
        input.arr_size = 0;
        input.data = nullptr;
    }

    DynamicArray& operator=(DynamicArray&& input) noexcept {
        std::cout<<"Move assignment c'tor\n";
        if (this != &input) {
            this->arr_size = input.arr_size;
            delete[] this->data;
            this->data = input.data;
            input.arr_size = 0;
            input.data = nullptr;
        }
        return *this;
    }

    ~DynamicArray() {
        std::cout<<"Destructor c'tor\n";
        delete [] data;
        arr_size = 0;
    }

private:
    size_t arr_size;
    uint8_t* data{nullptr};
};
// Rule of 5 END

// priority_queue START
struct Patient {
    std::string name{};
    uint8_t priority{}; // higher prio implies more urgent
};
struct CustomPatientComparator {
    bool operator()(const Patient& lhs, const Patient& rhs) const {
        return lhs.priority < rhs.priority;
    }
};
// priority_queue END


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

    // umap with custom hashable Key START
    std::unordered_map<Key, std::variant<Dog, Cat>, CustomKeyHash> my_map;
    my_map.emplace(Key{1, "Cat"}, cat);
    my_map.emplace(Key{2, "Dog"}, dog);
    // umap with custom hashable Key END

    // ranges & views START
    auto marshalled_data = std::views::iota(0, 7) | std::views::transform([](auto input){ return (input * 2);});
    std::cout << "ranges example: \n";
    for (auto data : marshalled_data) {
        std::cout << data << " ";
    }
    std::cout<<std::endl;
    // ranges & views END

    // priority_queue START
    std::priority_queue<uint8_t, std::vector<uint8_t>, std::greater<>> min_heap;
    min_heap.emplace(0);
    min_heap.emplace(1);
    min_heap.emplace(2);
    const auto min_ele = min_heap.top();
    printf("Min element: %d\n", min_ele);
    min_heap.pop();

    std::priority_queue<Patient, std::vector<Patient>, CustomPatientComparator> patients;
    patients.emplace(Patient{"John Doe", 64});
    patients.emplace(Patient{"Prince Habibi", 42});
    printf("Most urgent patient: %s with priority %d\n", patients.top().name.c_str(), patients.top().priority);
    patients.pop();
    // priority_queue END

    return 0;
}
