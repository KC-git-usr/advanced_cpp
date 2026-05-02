//
// Created by Kumar Chakravarthy on 02-May-23.
//
#include <iostream>
#include <map>


class Point{
private:
    float x;
    float y;

public:
    Point(float x_ = 0.0f, float y_ = 0.0f) :
            x(x_), y(y_) {}

    float getX() const {
        return this->x;
    }

    float getY() const {
        return this->y;
    }

    bool operator<(const Point& input) const {
        return (this->x < input.x);
    }
};

void Print(const std::map<Point, char> input) {
    for(const auto& pt : input) {
        std::cout << pt.first.getX() << ", " << pt.first.getY() <<", " << pt.second << std::endl;
    }
    std::cout << "-------------" << std::endl;
}

int main() {

    // custom map
    std::map<Point, char> point_obj{
            {Point(1.2, 2.5), 'a'},
            {Point(3.1, 6.5), 'b'},
            {Point(0.1, 7.5), 'c'}
    };

    Print(point_obj);

    point_obj.insert({Point(-1.1, 3.2), 'd'});

    Print(point_obj);

    std::map<Point, char> second_obj {
            {Point(5.5, 1.4), 'e'},
            {Point(7.8, -9.4), 'f'}
    };

    // merge
    point_obj.insert(second_obj.begin(), second_obj.end());

    Print(point_obj);
}