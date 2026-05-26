#include <atomic>
#include <iostream>
#include <queue>

// SPSC Queue START
template<typename T, size_t N>
class CustomQueue {
    std::array<T, N> ring_buffer_{};
    alignas(std::hardware_destructive_interference_size) std::atomic<size_t> head_{};
    alignas(std::hardware_destructive_interference_size) std::atomic<size_t> tail_{};
    char padding_[std::hardware_destructive_interference_size - sizeof(size_t)];
    static_assert(std::atomic<std::size_t>::is_always_lock_free);
    static_assert(N > 0);
public:
    auto Push(const T& input) -> bool {
        const auto head = head_.load(std::memory_order_relaxed);
        const auto tail = tail_.load(std::memory_order_acquire);
        if((head - tail) >= N) {
            return false;
        }
        ring_buffer_[head % N] = input;
        head_.store(head + 1, std::memory_order_release);
        return true;
    }
    auto Pop(T& buffer) -> bool {
        const auto head = head_.load(std::memory_order_acquire);
        const auto tail = tail_.load(std::memory_order_relaxed);
        if ((head - tail) == 0) {
            return false;
        }
        buffer = std::move(ring_buffer_[tail % N]);
        tail_.store(tail + 1, std::memory_order_release);
        return true;
    }
};
// SPSC Queue END

// SCHED_FIFO START
struct Task {
    std::string task_name{};
    int8_t priority{};

    bool operator<(const Task& rhs) const {
        return priority < rhs.priority;
    }
};
// SCHED_FIFO END

int main(int argc, const char * argv[]) {
    // SCHED_FIFO START
    // max heap
    std::priority_queue<Task, std::vector<Task>, std::less<>> task_pq;
    task_pq.push({"Task 1", 99});
    task_pq.push({"Task 4", -15});
    task_pq.push({"Task 2", 20});
    task_pq.push({"Task 3", -1});
    task_pq.push({"Task 5", -15});

    while (!task_pq.empty()) {
        const auto& task = task_pq.top();
        printf("Executing %s with priority %d\n", task.task_name.c_str(), task.priority);
        task_pq.pop();
    }
    // SCHED_FIFO END

    
}
