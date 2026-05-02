//
// Created by Kumar Chakravarthy on 09-Nov-23.
//
#include <chrono>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>

// generically this would be the resource accessor
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

// this way the member object ref count of the resource accessor does not increase
class Circle : public std::enable_shared_from_this<Circle>
{
private:
    float radius;
    std::shared_ptr<Point> center;
public:
    Circle(float radius_ = 0.0f) :
            radius(radius_), center(nullptr) {}
    // TODO: complete implement
};

void MyThreadSafeFunction(std::shared_ptr<Point> input_obj) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::shared_ptr<Point> internal_obj = input_obj;

    {
        static std::mutex io_mutex;
        std::lock_guard<std::mutex> lk(io_mutex);
        std::cout << "Local pointer in a thread: " << internal_obj.use_count() << std::endl;
    }
}

int main() {
    std::shared_ptr<Point> point_a = std::make_shared<Point>(1.2, 2.5);
    std::shared_ptr<Point> point_b = point_a;
    std::cout << "Ref count of point_a: " << point_a.use_count() << std::endl;
    std::cout << "-------------" << std::endl;

    std::shared_ptr<Circle> circle_obj = std::make_shared<Circle>(3.4);
    std::cout << "Ref count of circle_obj: " << circle_obj.use_count() << std::endl;
    std::cout << "-------------" << std::endl;

    std::shared_ptr<Point> point_obj = std::make_shared<Point>(1.4, 4.2);
    std::cout << "Ref count of point_obj: " << point_obj.use_count() << std::endl;
    std::thread t1(MyThreadSafeFunction, point_obj), t2(MyThreadSafeFunction, point_obj), t3(MyThreadSafeFunction, point_obj);
    std::cout << "Ref count of point_obj after spawning 3 threads using this obj: " << point_obj.use_count() << std::endl;
    std::cout << "-------------" << std::endl;
    t1.join();
    t2.join();
    t3.join();

    return 0;
}