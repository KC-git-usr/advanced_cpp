#include <iostream>
#include <bits/stdc++.h>

using namespace std;

struct Shape {
    virtual pair<float, float> getPoint() = 0;
    virtual vector<float> getShapeParameters() = 0;
    virtual ~Shape() {
        cout<<"shape object was destroyed"<<endl;
    }
};


struct Circle : public Shape {
    float x, y, radius;
    Circle(float x_, float y_, float radius_) :
        x(x_),
        y(y_),
        radius(radius_) {}

    ~Circle() {
        cout<<"Circle destructor called"<<endl;
    }
        
    pair<float, float> getPoint() override{
        return make_pair(x,y);
    }

    vector<float> getShapeParameters() override{
        return {radius};
    }

    void circleFunction() {
        cout<<"Called circleFunction"<<endl;
    }

};


struct Rectangle : public Shape {

    float x, y, length, width; // x,y of bottom left corner

    Rectangle(float x_, float y_, float length_, float width_) :
        x(x_),
        y(y_),
        length(length_),
        width(width_) {}

    pair<float, float> getPoint() override{
        return make_pair(x,y);
    }

    vector<float> getShapeParameters() override{
        return {length, width};
    }

    void rectangleFunction() {
        cout<<"Called rectangleFunction"<<endl;
    }

};


int main()
{
    Circle* circle1 = new Circle(1.0,1.0,2.0);
    Circle* circle2 = new Circle(1.0,1.0,2.0);
    Rectangle* rectangle1 = new Rectangle(1.0,3.0,3.0,5.0);
    Rectangle* rectangle2 = new Rectangle(1.0,3.0,3.0,5.0);

    cout<<"Circle data: "<<endl;
    cout<<"x = "<<circle1->x<<endl;
    cout<<"y = "<<circle1->y<<endl;
    cout<<"radius = "<<circle1->radius<<endl;

    cout<<"Rectangle data: "<<endl;
    cout<<"x = "<<rectangle1->x<<endl;
    cout<<"y = "<<rectangle1->y<<endl;
    cout<<"length = "<<rectangle1->length<<endl;
    cout<<"width = "<<rectangle1->width<<endl;

    vector<Shape*> shape_vector;
    shape_vector.push_back(circle1);
    shape_vector.push_back(rectangle1);
    shape_vector.push_back(circle2);
    shape_vector.push_back(rectangle2);

    cout<<"Retrieved x of circle = "<<(shape_vector[0]->getPoint()).first<<endl;
    cout<<"Retrieved radius of circle = "<<shape_vector[0]->getShapeParameters()[0]<<endl;
    cout<<"Retrieved y of rectangle = "<<(shape_vector[1]->getPoint()).second<<endl;
    cout<<"Retrieved width of rectangle = "<<shape_vector[1]->getShapeParameters()[1]<<endl;

    delete circle1;
    delete rectangle1;
    shape_vector.clear();

    return 0;
}
