//
// Created by Kumar Chakravarthy on 11/2/2022.
//
#include <functional>
#include <queue>
#include <vector>
#include <iostream>


template<typename T>
void print(T const& q) {
    std::cout << ": \t";
    for (auto const& n : q)
        std::cout << n << ' ';
    std::cout << '\n';
}

template<typename Q>
void print_queue(Q q) {
    // NB: q is passed by value because there is no way to traverse
    // priority_queue's content without erasing the queue.
    for (std::cout << ": \t"; !q.empty(); q.pop())
        std::cout << q.top() << ' ';
    std::cout << '\n';
}

int Add(int a, int b) {
    return (a + b);
}

struct Node {
    double time_stamp;
    double value;
    Node* next_ptr;
};

void ComplexPriorityQueue() {
    std::priority_queue<Node*, std::vector<Node*>, std::greater<Node*>> time_queue;
}

int main() {
    const auto data = {1,8,5,6,3,4,0,9,7,2};
    std::cout<< " Input data\n";
    print(data);

    std::priority_queue<int> q1; // Max priority queue
    for(int n : data)
        q1.push(n);

    std::cout<< " q1 data\n";
    print_queue(q1);

    // Min priority queue
    // std::greater<int> makes the max priority queue act as a min priority queue
    std::priority_queue<int, std::vector<int>, std::greater<int>>
            minq1(data.begin(), data.end());

    std::cout<< " minq1 data\n";
    print_queue(minq1);

    // Second way to define a min priority queue
    std::priority_queue<int, std::vector<int>, std::greater<int>> minq2(data.begin(), data.end(), std::greater<int>());

    std::cout<< " minq2 data\n";
    print_queue(minq2);

    // Using a custom function object to compare elements.
    struct {
        bool operator() (const int l, const int r) const { return l > r; }
    } customLess;
    std::priority_queue<int, std::vector<int>, decltype(customLess)> minq3(data.begin(), data.end(), customLess);

    std::cout<< " minq3 data\n";
    print_queue(minq3);

    // Using lambda to compare elements.
    auto cmp = [](int left, int right) { return (left ^ 1) < (right ^ 1); };
    std::priority_queue<int, std::vector<int>, decltype(cmp)> q5(cmp);

    for(int n : data)
        q5.push(n);

    std::cout<< " q5 data\n";
    print_queue(q5);

    std::vector<int> input{1,2,3,-1};
    std::priority_queue<int, std::vector<int>, std::greater<int>> pq(input.begin(), input.end(), std::greater<int>());
    while(!pq.empty()) {
        std::cout<<pq.top()<<" ";
        pq.pop();
    }
}
