//
// Created by Kumar Chakravarthy on 09-Nov-23.
//
#include <iostream>
#include <thread>

void Hello() {
    std::cout << "Hello, World!" << std::endl;
}

int main() {
    std::thread t(Hello);
    t.join();

    return 0;
}
