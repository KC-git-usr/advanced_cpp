#include <iostream>
#include <thread>
#include <vector>
#include <unordered_map>
#include <functional>

// Function foo that behaves differently based on the thread ID
void foo(const std::unordered_map<std::thread::id, std::function<void()>>& actions) {
    std::thread::id this_id = std::this_thread::get_id();
    if (actions.find(this_id) != actions.end()) {
        actions.at(this_id)();
    } else {
        std::cout << "No specific action for this thread." << std::endl;
    }
}

int main() {
    // Container for thread IDs
    std::vector<std::thread::id> thread_ids;
    // Map to associate thread IDs with specific actions
    std::unordered_map<std::thread::id, std::function<void()>> actions;

    // Define the threads
    std::thread t1([&thread_ids, &actions]() {
        thread_ids.push_back(std::this_thread::get_id());
        actions[std::this_thread::get_id()] = []() {
            std::cout << "foo() called from thread 1" << std::endl;
        };
        foo(actions);
    });

    std::thread t2([&thread_ids, &actions]() {
        thread_ids.push_back(std::this_thread::get_id());
        actions[std::this_thread::get_id()] = []() {
            std::cout << "foo() called from thread 2" << std::endl;
        };
        foo(actions);
    });

    // Wait for threads to finish
    t1.join();
    t2.join();

    return 0;
}
