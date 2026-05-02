//
// Created by Kumar Chakravarthy on 10/18/2022.
//


#include <iostream>
#include <bits/stdc++.h>

/*
Get input points
for(point:(input-1))
    Get point A and the next after point A = point B
    Calc the no of points that can be between 2 consecutive input points, i.e., point A and point B
        For 1,1 and 1,5 and D=1
        n = 3 (excluding the input points themselves)
        n = int((distance b/w A and B)/D - 2); //take floor
    while n>0
        calc i_point at n*D from first input point
            get equation of line joining point A and point B: y = mx + c;
                        *
                x
            *
            r = step_distance / total_distance = n*D/t_D;
            i_point_x = Ax + (n*D)*(Bx-Ax)/t_D; = Ax + r(Bx-Ax) = (1-r)Ax + rBx
            i_point_y = (1-r)Ax + rBx
        n--;
*/

int main() {

    std::array<std::pair<float, float>, 2> input {{
                                                          {1.0,1.0},
                                                          {1.0,5.0}
                                                  }};

    float distance = 1.0;

    for(auto point:input) {
        std::cout<<point.first<<", "<<point.second<<std::endl;
    }

    return 0;
}
