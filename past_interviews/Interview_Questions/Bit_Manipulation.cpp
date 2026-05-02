//
// Created by Kumar Chakravarthy on 09-May-23.
//

#include <iostream>
#include <bitset>
#include <stdlib.h>


char Bit_get(unsigned char* value, unsigned char bit_number) {
    unsigned char copy_of_value = *value;

    while (bit_number-- > 0)
        copy_of_value >>= 1;

    return (copy_of_value & 1);
}


char Bit_set(unsigned char* value, unsigned char bit_number) {
    unsigned char mask = 0b00000001;

    while(bit_number-- > 0)
        mask <<= 1;

    return (mask | *value);
}


char Bit_clear(unsigned char* value, unsigned char bit_number) {
    unsigned char mask = 0b00000001;

    while(bit_number-- > 0)
        mask <<= 1;

    mask = ~mask;

    return (mask & *value);
}


int main() {
    unsigned char input_value_1 = 0b00001001;
    unsigned char input_bit_number_1 = 3;
    unsigned char input_value_2 = 0b00001011;
    unsigned char input_bit_number_2 = 2;
    std::bitset<8> x;

    x = Bit_get(&input_value_1, input_bit_number_1);
    std::cout << "O/P of Bit_get : " << x << std::endl;

    x = Bit_set(&input_value_1, input_bit_number_2);
    std::cout << "O/P of Bit_set : " << x << std::endl;

    x = Bit_clear(&input_value_2, input_bit_number_2);
    std::cout << "O/P of Bit_clear : " << x << std::endl;

    x = Bit_clear(&input_value_2, input_bit_number_1);
    std::cout << "O/P of Bit_clear : " << x << std::endl;

    unsigned char input_value_3 = 0xf;
    unsigned char input_bit_number_3 = 3;

    x = Bit_get(&input_value_3, input_bit_number_3);
    std::cout << "O/P of Bit_get : " << x << std::endl;

    x = Bit_set(&input_value_3, input_bit_number_3);
    std::cout << "O/P of Bit_set : " << x << std::endl;

    x = Bit_clear(&input_value_3, input_bit_number_3);
    std::cout << "O/P of Bit_set : " << x << std::endl;

    int right;
    for(int i = 0; i < 10; ++i) {
        right = rand() % 2;
        std::cout << "right : " << right << std::endl;
    }
}