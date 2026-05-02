//
// Created by Kumar Chakravarthy on 29-Dec-22.
//

#include <iostream>
#include <bits/stdc++.h>


template<typename T>
void Print(const T& input) {
    std::cout<<std::endl;
    for (auto it = input.begin(); it != input.end() ; ++it)
        std::cout<< *it<< ' ';
    std::cout<<std::endl;
}


int main() {

    // initialize vectors
    std::vector<int> v1{1, 2, 3, 4, 5};
    std::vector<int> v2{6, 7, 8, 9, 10};
    std::vector<int> v3;

    //reverse the vector
    std::reverse(v1.begin(), v1.end());

    std::cout<< "v1 : ";
    Print(v1);

    // get min element
    auto v_it_to_min = std::min_element(v1.begin(), v1.end());
    std::cout<< "Min element of input vector = "<< *v_it_to_min << std::endl;

    //merge the 2 vectors  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    std::merge(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(v3));

    std::cout<< "v3 : ";
    Print(v3);

    //in-place merge of 2 vectors  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    v1.insert(v1.begin(), v2.begin(), v2.end());
    std::cout<< "Merged v1 and v2 : ";
    Print(v1);


    // initialize the list
    std::list<int> l{6, 7, 8, 9, 10};

    // reverse the list
    std::reverse(l.begin(), l.end());

    std::cout<< "l : ";
    Print(l);

    // get min element
    auto l_it_to_min = std::min_element(l.begin(), l.end());
    std::cout<< "Min element of input list = "<< *l_it_to_min << std::endl;

    // initialize the pairs
    std::pair<int, char> p1 {1, 'a'};
    std::cout<< "Pair : " << p1.first << ", " << p1.second <<std::endl;

    // initialize the maps
    std::map<char, int> m {
            {'a', 1},
            {'b', 2},
            {'c', 3},
            {'d', 4}
    };

    std::cout<< "m : " <<std::endl;

    // erase a pair by passing the key
    m.erase('c');
    for(auto & it : m)
        std::cout<< it.first << ", " << it.second << std::endl;

    // initialize priority queue
    std::priority_queue<int> pq;
    pq.push(5);
    pq.push(4);
    pq.push(1);
    pq.push(6);

    std::cout<< "Max element from priority queue: " << pq.top();

    // initialize priority queue with custom comparator
    auto CustomCmp = [](std::pair<int, int> var1, std::pair<int, int> var2) {
            return var1.first > var2.first;
    };
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(CustomCmp)> pq2(CustomCmp);
    pq2.push({3, 1});
    pq2.push({5, 3});
    pq2.push({1, 4});

    // print elements of priority_queue
    std::cout<<"\nPriority queue : ";
    while(!pq2.empty()) {
        std::cout<<(pq2.top()).first<<", "<<(pq2.top()).second<<" | ";
        pq2.pop();
    }

}