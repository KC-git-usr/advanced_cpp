//
// Created by Kumar Chakravarthy on 11/2/2022.
//
#include <iostream>


template<typename T>
void foo(T input) {
    std::cout<<input<<std::endl;
}


template<typename To, typename From>
To bar(From input) {
    return input;
}


int main() {

    float input {5.6f};

    foo(input);  // equivalent to foo<float>(input)
    foo<int>(input);  // here I'm casting input from float to int

    std::cout<<bar<float>(input)<<std::endl;  // equivalent to bar<float, float>(input) -> bar<To, From>(input)
    std::cout<<bar<float, int>(input)<<std::endl;  // float -> To and int -> From

    return 0;
}