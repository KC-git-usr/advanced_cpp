//
// Created by Kumar Chakravarthy on 02-May-23.
//
#include <iostream>
#include <set>

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

void Print(const std::set<Point> input) {
    for(const auto& pt : input) {
        std::cout << pt.getX() << ", " << pt.getY() << std::endl;
    }
    std::cout << "-------------" << std::endl;
}

int main() {

    // custom set
    std::set<Point> point_obj{
        Point(1.2, 2.5),
        Point(3.1, 6.5),
        Point(0.1, 7.5)
    };

    Print(point_obj);

    point_obj.insert(Point(-1.1, 3.2));

    Print(point_obj);

    std::set<Point> second_obj {
        Point(5.5, 1.4),
        Point(7.8, -9.4)
    };

    // merge
    point_obj.insert(second_obj.begin(), second_obj.end());

    Print(point_obj);
}