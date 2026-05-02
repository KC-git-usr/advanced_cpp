//
// Created by Kumar Chakravarthy on 07-May-23.
//

#include <iostream>
#include <bits/stdc++.h>

//template<class T>
//void stripCOnst(T arg) {
//    typename std::remove_const<T>::type new_arg;
//
//    if(std::is_const<decltype(new_arg)>::value)
//        std::cout<<"Yes"<< std::endl;
//    else
//}

int getL() {
    return 10;
}

class Vec {
private:
    double ivec, jvec;
public:
    Vec(double i, double j) : ivec(i), jvec(j) {}
    Vec(const Vec& rhs) : ivec(rhs.ivec), jvec(rhs.jvec) {}
};

template<class T>
class tClass {
public:
    T data;
};

double& calculateC(double r){
    double c;
    c = (2*3.14) * r;
    return c;
}


int main() {
//    int sz = getL();
//    char message[sz];
//
//    int num;
//    num = 10.0;
//
//    for(char c = 0; c < 250; c++)
//        std::cout << "1"
//
//    Vec vec1(2, -6);
//    constexpr Vec vec2(vec1);
//    enum DAY {Mon = 11, Tue = 12};
//    enum DAY var = Mon;
//    tClass i<int>;
    tClass<int> i;
//    tClass i(int);
// <int> tClass i;
// tClass(int) i;
    const double& val = calculateC(10.0);
    std::cout << val << std::endl;
}

