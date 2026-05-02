//
// Created by Kumar Chakravarthy on 03-Feb-23.
//

// 2 arrays
// combine using ptrs

#include <bits/stdc++.h>
#include <memory>
#include <iostream>
#include <string.h>

static const int size_a = 3;
static const int size_b = 2;

int main() {
    int array_a[size_a] {1,2,3};
    int array_b[size_b] {4,5};
    int array_c[size_a + size_b];

    int *ptr_a = array_a;
    int *ptr_b = array_b;
    int *ptr_c = array_c;

    memcpy(ptr_c, ptr_a, size_a * sizeof (int));
    memcpy(ptr_c + size_a, ptr_b, size_b * sizeof (int));

    int *result = (ptr_c + size_a + size_b);

    for(auto ptr = ptr_c; ptr != result; ++ptr)
        std::cout<<*ptr<<" ";

}