//
// Created by Kumar Chakravarthy on 03-Feb-23.
//

#include <vector>

int main() {
    std::vector<int> v1 {1, 2, 3};
    v1.push_back(4);
    v1.clear();
    bool flag = v1.empty();
    v1.push_back(5);
    v1.push_back(6);
    v1.push_back(7);
    v1.size();
    v1.insert(v1.begin(), 12);
}
