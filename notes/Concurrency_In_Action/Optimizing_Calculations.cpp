//
// Created by Kumar Chakravarthy on 11-Dec-23.
//
#include <math.h>

#include <Eigen/Dense>

#include <chrono>
#include <iostream>
#include <string>
#include <vector>

// When an object of this class is destroyed, the timer is automatically calculated and printed
// Object must be declared at the very beginning of the function definition you want to time
struct ScopedTimer {
    std::chrono::steady_clock::time_point start;
    const std::string function_name;
    ScopedTimer(const std::string name) :
            function_name(name) {
        start = std::chrono::steady_clock::now();
    }
    ~ScopedTimer() {
        auto end = std::chrono::steady_clock::now();
        std::cout << "Time taken for \"" <<function_name<<"()\" to execute was: "<<std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microseconds" << std::endl;
    }
};

template<typename T>
void Print(const T& input) {
    ScopedTimer scoped_timer_bomb(__FUNCTION__ );
    if(typeid(T) == typeid(std::vector<std::vector<int>>)) {
        for(const auto& row : input) {
            for(const auto& val : row)
                std::cout << val << " ";
            std::cout << std::endl;
        }
    }
}

// Pass by reference
void NoobTransform(std::vector<std::vector<int>>& input) {
    ScopedTimer scoped_timer_bomb(__FUNCTION__ );
    for(auto& row : input) {
        for(auto& val : row) {
            val *= 2; // or do whatever you want
        }
    }
}

void BigBrainTransform(Eigen::MatrixXi& matrix) {
    ScopedTimer scoped_timer_bomb(__FUNCTION__);
    matrix *= 2; // Element-wise operation for the entire matrix
}

int main() {
    std::cout << "Speed!" << std::endl;

    // Let's say you don't know the size of the vectors beforehand
    // m = rows, n = columns
    int m1= 1, n1 = 2;
    int m2 = 2, n2 = 3;

    std::vector<std::vector<int>> result (m1, std::vector<int>(n2, 1));

    Print(result);

    NoobTransform(result);
    Print(result);

    Eigen::MatrixXi eigen_result = Eigen::MatrixXi::Constant(m1, n2, 1);
    BigBrainTransform(eigen_result);
    Print(result);

    return 0;
}
