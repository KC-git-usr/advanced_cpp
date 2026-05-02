//
// Created by Kumar Chakravarthy on 20-Apr-23.
//

#include <iostream>
#include <unordered_set>
#include <vector>

class Point {
public:
    int x_;
    int y_;
    Point(): x_(0), y_(0) {}
    Point(int x, int y): x_(x), y_(y) {}

    // Note: this must be declared const
    bool operator==(const Point& rhs) const {
        return ((this->x_ == rhs.x_) && (this->y_ == rhs.y_));
    }

    struct HashFunction {
        // Note: this must be declared const
        /*
         * This function is an implementation of a hash function for a custom data type called "Point".
         * Hash functions are used to convert data of arbitrary size into a fixed-size hash value, typically
         * a 32- or 64-bit integer. Hash functions are commonly used in data structures like hash tables,
         * which allow for efficient lookups and insertion of data. The purpose of the hash function in this
         * context is to allow instances of the Point class to be used as keys in a hash table. The function
         * takes a Point object as input and computes a hash value based on the x and y coordinates of the point.
         * The hash values for x and y are computed using the std::hash function for integers, which is a
         * built-in hash function in the C++ standard library. The hash values for x and y are then combined
         * using the bitwise XOR operator to produce the final hash value. The shift operator (<<) is used to
         * ensure that the hash value for y has a different bit pattern than the hash value for x, which helps to
         * reduce collisions in the hash table. Overall, this function allows instances of the Point class to be
         * used as keys in a hash table, providing efficient lookups and insertion of data based on the x and y
         * coordinates of the point.
         * */
        size_t operator()(const Point& input) const {
            size_t x_hash = std::hash<int>()(input.x_);
            size_t y_hash = std::hash<int>()(input.y_) << 1;
            return x_hash ^ y_hash;
        }
    };
};

int main() {
    std::unordered_set<Point, Point::HashFunction> my_hash_set;
    my_hash_set.insert(Point(3, 6));
    my_hash_set.insert((Point(7, 4)));
    my_hash_set.insert((Point(7, -4)));

    for(auto& pt : my_hash_set)
        std::cout << "x : " << pt.x_ << ", y : " << pt.y_ << std::endl;
}