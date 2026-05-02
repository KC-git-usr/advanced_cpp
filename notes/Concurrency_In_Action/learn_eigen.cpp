//
// Created by Kumar Chakravarthy on 11-Dec-23.
//
#include <Eigen/Dense>
#include <iostream>

int main() {

    // Dynamic(heap) - resizable (> 32 elements)
    Eigen::MatrixXi matrix_dyn_a;
    Eigen::MatrixXi matrix_dyn_b(3, 3);
    // Initialize/Insert
    matrix_dyn_b << 1, 2, 3,
                    4, 5, 6,
                    7, 8, 9;
    std::cout << matrix_dyn_b << std::endl;

    // Static(stack) - fixed (< 16 elements)
    Eigen::Matrix3i matrix_fixed_a(3, 3);
    Eigen::Matrix3i matrix_fixed_b(4, 4) = Eigen::Matrix3i::Random();
    matrix_fixed_a << 10, 11, 12,
                    13, 14, 15,
                    16, 17, 18;
    std::cout << matrix_fixed << std::endl;

    int m = 3, n = 4;
    Eigen::Matrix<int, m, n> my_matrix; // I recommend this way of initializing a matrix

    // A Vector in Eigen is a vertical matrix (by default)
    Eigen::VectorXi my_vector(3);
    my_vector << 1, 2, 3;

    // Convert to array for element-wise operations
    Eigen::MatrixXi new_matrix = my_vector.array() + 1;
    std::cout << new_matrix << std::endl;
    Eigen::MatrixXi new_matrix = my_matrix.array() + 1;
    std::cout << new_matrix << std::endl;

    return 0;
}
