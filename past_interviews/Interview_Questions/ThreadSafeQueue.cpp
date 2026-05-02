#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class ThreadSafeQueue {
public:
    ThreadSafeQueue() = default;

    void Push(const T& item) {
        std::lock_guard<std::mutex> lock(mutex_);
        queue_.push(item);
        condition_.notify_one();
    }

    bool Pop(T& item) {
        std::unique_lock<std::mutex> lock(mutex_);
        condition_.wait(lock, [this] { return !queue_.empty(); });
        if (!queue_.empty()) {
            item = queue_.front();
            queue_.pop();
            return true;
        }
        return false;
    }

    bool IsEmpty() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.empty();
    }

private:
    std::queue<T> queue_;
    mutable std::mutex mutex_;
    std::condition_variable condition_;
};


int main() {
    ThreadSafeQueue<int> my_custom_queue;
    std::cout<< my_custom_queue.IsEmpty() << std::endl;
    my_custom_queue.Push(5);
    my_custom_queue.Push(3);
    my_custom_queue.Push(6);
    std::cout<< my_custom_queue.IsEmpty() << std::endl;
    int ele = 5;
    if (my_custom_queue.Pop(ele))
        std::cout << "Pop successful" << std::endl;
}