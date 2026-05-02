//
// Created by Kumar Chakravarthy on 26-Nov-23.
//
#include <iostream>
#include <optional>
#include <string>

std::optional<std::string> Foo(const int& input) {
    if (input > 0) {
        return std::to_string(input);
    }
    return std::nullopt;
}

int main() {
    std::optional<std::string> result_1 = Foo(0);
    std::optional<std::string> result_2 = Foo(6);

    std::cout << result_1.value_or("Input to Foo was 0, cannot process") << std::endl;

    if(result_2.has_value()) { // has_value() is optional, using just result_2 in the if stmt will also work
        std::cout << result_2.value() << std::endl;
    }
    return 0;
}
