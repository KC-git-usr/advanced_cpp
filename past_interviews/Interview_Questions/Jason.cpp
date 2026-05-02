//
// Created by Kumar Chakravarthy on 18-May-23.
//

// TIL : return type of function used in for_each MUST be void
// TIL : iterators of containers when dereferenced, change the underlying value too (returns a non-const pointer)
//       for example: *std::max_element(my_vec.begin(), my_vec.end()) = -1; will set the max element
//       in the original container to -1
// TIL : Time complexity of priority queue: building pq from an existing data is O(n)
//       But building pq by inserting data element by element is O(n*log(n)), a.k.a. maintaining a pq

#include <algorithm>
#include <bitset>
#include <iostream>
#include <math.h>
#include <memory>
#include <queue>
#include <string>
#include <unordered_set>
#include <vector>


// Simple Algorithm start
void simpleAlgorithm(int n) {
    int steps = 0;
    while(n != 1) {
        if(n < 1) {
            std::cout << "Invalid number encountered" << std::endl;
            return;
        }
        n = (n % 2 == 0) ? n / 2 : 3 * n + 1;
        steps++;
    }

    std::cout << "Number of steps: " << steps << std::endl;
}
// Simple Algorithm end


// One Edit Away start
bool oneEditAway(const std::string& s1, const std::string& s2) {
    int ptr_1 = 0, ptr_2 = 0, diff = 0;
    while(ptr_1 < s1.length() && ptr_2 < s2.length()) {
        if(diff > 1)
            return false;
        if(s1[ptr_1] == s2[ptr_2]) {
            ptr_1++;
            ptr_2++;
        } else {
            // move ptr_1 or ptr_2 or both ptr one step
            if((ptr_1 + 1 < s1.length()) && (s1[ptr_1 + 1] == s2[ptr_2]))
                ptr_1++;
            else if((ptr_2 + 1 < s2.length()) && (s1[ptr_1] == s2[ptr_2 + 1]))
                ptr_2++;
            else {
                ptr_1++;
                ptr_2++;
            }
            diff++;
        }
    }

    if(ptr_1 == s1.length()) {
        diff += s2.length() - ptr_2;
    }
    if(ptr_2 == s2.length()) {
        diff += s1.length() - ptr_1;
    }

    return (diff > 1) ? false : ((diff == 0) ? false : true);
}
// One Edit Away end


// Supermarket queue start
// Idea:
// Maintain a queue for each terminal and each terminal cumulative waiting time
// if any terminal empty, then add person to that terminal queue
// if none terminal empty, find out the smallest wait time of all queues, (pop smallest ele from frontier line and subtract it from every other queue)
// then add person to terminal with shortest total curr waiting time
// maintain a total_time for each queue by simply adding every ele that enters the queue
// Additional readings :
// https://stackoverflow.com/questions/31208640/what-is-the-difference-between-cbegin-and-begin-for-vector
// https://www.codewars.com/kata/57b06f90e298a7b53d000a86/solutions/cpp
int supermarketQueue(const std::vector<int>& line, const int& terminals) {
    std::vector<std::queue<int>> terminal_queue (terminals);  // vector of queues for terminal states
    std::vector<int> terminal_time (terminals, 0); // vector of total time for each queue
    bool person_sent_to_empty_terminal = false;

    for(int i = 0; i < line.size(); ++i) {
        for(int j =0; j < terminals; ++j) {
            if(terminal_queue[j].empty()) {
                terminal_queue[j].push(line[i]);
                terminal_time[j] += line[i];
                person_sent_to_empty_terminal = true;
                break;
            }
        }
        if(person_sent_to_empty_terminal == false) {
            auto it = std::min_element(terminal_time.begin(), terminal_time.end());
            int pos = std::distance(terminal_time.begin(), it);
            terminal_queue[pos].push(line[i]);
            terminal_time[pos] += line[i];
        }
        person_sent_to_empty_terminal = false;
    }

    return *std::max_element(terminal_time.begin(), terminal_time.end());
}

long queueTime(std::vector<int> customers,int n){
    std::vector<long> queues(n, 0);

    for (int i : customers)
        *std::min_element(queues.begin(), queues.end()) += i;

    return *std::max_element(queues.cbegin(), queues.cend());
}
// Supermarket queue end


// min sum in N operations start
int minSum(const std::vector<int>& input, const int& k) {
    int sum = 0, n = k;
    std::priority_queue<int, std::vector<int>, std::less<int>> my_pq (input.begin(), input.end(), std::less<int>());

    int element;
    while(n--) {
        element = my_pq.top();
        my_pq.pop();
        element = std::ceil(element / 2);
        my_pq.push(element);
    }

    n = k;
    while (n--) {
        element = my_pq.top();
        my_pq.pop();
        sum += element;
    }

    return sum;
}
// min sum in N operations end


// Template specialization start
class Player {
private:
    int m_age;
public:
    Player(int age) : m_age(age) {}
    int getAge() {
        return this->m_age;
    }
    bool operator<(const Player& input) {
        return this->m_age < input.m_age;
    }
};

template<typename T>
T minimum(T a, T b) {
    return (a < b) ? a : b;
}

template<>
Player minimum(Player a, Player b) {
    return (a < b) ? a : b;
}
// Template specialization end


// Inheritance/Polymorphism Q start
class Parent {
public:
    void print() {
        std::cout << "Parent print function\n";
    }
    void invoke() {
        std::cout << "Parent invoke function\n";
        this->print();
    }
};

class Child : public Parent {
public:
    void print() {
        std::cout << "Child print function\n";
    }
    void invoke() {
        std::cout << "Child invoke function\n";
        this->print();
    }
};
// Inheritance/Polymorphism Q end


// Remove all duplicate integers start
std::vector<int> removeDuplicates(std::vector<int> input) {
    std::unordered_set<int> hash_set;
    int ptr_fetch = 0;
    for(int i = 0; i < input.size(); ++i) {
        if(hash_set.find(input[i]) == hash_set.end()) {
            hash_set.insert(input[i]);
            input[ptr_fetch++] = input[i];
        }
    }
    return input;
}
// Remove all duplicate integers end


// All permutations of string start
void dfs(std::string& input, int start) {
    if (start == input.size()) {
        std::cout << input << std::endl;
        return;
    }
    for (size_t i = start; i < input.size(); i++) {
        std::swap(input[i], input[start]);
        dfs(input, start + 1);
        std::swap(input[i], input[start]);
    }
}

void permute(std::string input) {
    std::string copy(input);
    dfs(copy, 0);
}
// All permutations of string end


int main() {

    // Simple Algorithm
    if(false) {
        std::vector<int> test_num {12, 20, 97, 256, 6171, 2000000001};
        for_each(test_num.begin(), test_num.end(), simpleAlgorithm);
    }

    // One Edit Away
    if(false) {
        std::vector<std::pair<std::string, std::string>> test_input {
                {"abcd", "abc"},
                {"abde", "aebd"},
                {"abcd", "abfcd"},
                {"geeks", "geek"},
                {"geeks", "geeks"},
                {"geaks", "geeks"},
                {"peaks", "geeks"}
        };
        for(const auto& ele : test_input)
            std::cout << oneEditAway(ele.first, ele.second) <<std::endl;
    }

    // Supermarket Queue
    if(false) {
        std::vector<std::vector<int>> test_input_line {
                {3, 4, 5},
                {5,3,4},
                {10,2,3,3},
                {10,2,3,3,10},
                {2,3,10}
        };
        std::vector<int> test_input_terminals {
            2,
            1,
            2,
            2,
            2
        };
        for (int i = 0; i < 5; ++i) {
            std::cout << supermarketQueue(test_input_line[i], test_input_terminals[i]) << std::endl;
            std::cout << queueTime(test_input_line[i], test_input_terminals[i]) << std::endl;
        }
    }

    // container.begin() vs container.cbegin()
    if(false) {
        std::vector<int> my_vec{1, 2, 3, 4};
        std::cout << *std::max_element(my_vec.begin(), my_vec.end()) << std::endl;
        *std::max_element(my_vec.begin(), my_vec.end()) = -1;
        std::cout << *std::min_element(my_vec.begin(), my_vec.end()) << std::endl;
    }

    // min sum
    if(false) {
        std::vector<std::vector<int>> test_input_list {
                {10,5,7,20}
        };
        std::vector<int> test_input_k {
            4
        };
        for (int i = 0; i < 1; ++i) {
            std::cout << minSum(test_input_list[i], test_input_k[i]) << std::endl;
        }
    }

    // Template specialization
    if (false) {
        std::cout << minimum(3, 6) << std::endl;
        Player obj_1 {25};
        Player obj_2 {27};
        std::cout << minimum(obj_1, obj_2).getAge() << std::endl;
    }

    // Inheritance/Polymorphism Q
    if (false) {
        std::unique_ptr<Parent> p(new Child());
        p->invoke();
    }

    // Memset from cpp-reference docs
    if (false){
        int x = 0b111100000011;
        std::cout << x << std::endl;
        unsigned char y = static_cast<unsigned char>(0b111100000011);
        std::cout << y << std::endl;
        std::bitset<8> z(y);
        std::cout << z << std::endl;
    }

    // Remove Duplicates
    if (false) {
        std::vector<std::vector<int>> test_input {
                {10,5,7,20},
                {7,4,1,6,7,4,2},
                {7,7,1,6,7,4,2},
                {7,1,6,7,4,4},
                {7,1,6,6,4,5},
        };
        for (int i = 0; i < test_input.size(); ++i) {
            auto result = removeDuplicates(test_input[i]);
            for(const auto& ele : result)
                std::cout << ele << " ";
            std::cout << std::endl;
        }
    }

    // All permutations of string
    if (true) {
        std::vector<std::string> test_input {
                {"abc"},
                {"kum"}
        };
        for(size_t i = 0; i < test_input.size(); ++i) {
            permute(test_input[i]);
            std::cout << "-------------" << std::endl;
        }
    }
}
