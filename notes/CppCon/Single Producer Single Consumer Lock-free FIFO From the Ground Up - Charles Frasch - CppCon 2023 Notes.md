Original source: https://www.youtube.com/watch?v=K3P_Lmq6pw0
Presentation slides: https://github.com/CppCon/CppCon2023/blob/main/Presentations/SPSC_Lock-free_Wait-Free_Fifo_from_the_Ground_Up_CppCon_2023.pdf
Source code: https://github.com/CharlesFrasch/cppcon2023

# Notes:

- First, take a look at Boost Lockfree - spsc_queue.hpp . There are other well known variations too. Writing one yourself should only be done if these don't meet your requirements (very high chances you don't need to implement one yourself)
- https://www.boost.org/doc/libs/1_80_0/doc/html/lockfree.html
- https://www.1024cores.net/home/lock-free-algorithms/queues/unbounded-spsc-queue <- recommended to take a look

- **Objective**: design a single producer, single consumer, lock-free, wait-free, fifo
- Every word above has a meaning: 1 writer-thread, 1 reader-thread, no mutex, each thread is proceeding forward with the rest of its work regardless of other threads, a fixed size circular buffer which processes oldest entry first
- using a spsc may improve/degrade your performance- always measure! you may be better off using a single thread sometimes. Measure throughput, resilience to msg traffic spikes.
- disadvantages of spsc lock+wait free queue is managing 2 threads and higher memory usage.
- Basic implementation of a circular fifo- have a fixed size buffer linked end-to-end, have a push cursor/pointer, have a pop cursor/pointer. Algorithm looks like this:
- when `pushCursor == popCursor`, circular fifo is empty
- `++pushCursor` after element is pushed to buffer, `--popCursor` after element is popped from buffer, ensure cursor wrap around when index goes out of bounds
- if empty and you try to pop, you return false
- if full and you try to push, you can choose 2 implementations- overwrite oldest value OR return false
- See ss 1 and 2. Note: we are maintaining references to the elements in our ring buffer
- `std::allocator_traits::allocate()` - allocates size of `<T>` * capacity [in bytes], as if a global `new` operator were used, then starts the lifetime of an array of `<T>`, in that storage location, but doesn't start the lifetime of any `<T>`'s
- push takes in const ref, pop takes in ref and modifies in place, these are 2 intentional optimizations. Note how the destructor of `<T>` is intentionally called in the `pop()` function
- Kumar's comment: I found his benchmarking code very insightful- https://github.com/CharlesFrasch/cppcon2023/blob/main/bench.hpp
- The above implementation will give rise to 4 data races! (use tsan to verify). see ss 3. essentially `pushCursor` and `popCursor` are being modified and read by 2 independent threads, same situation occurs when 1 thread pushes to the ring buffer at the same time as another thread popping from the ring buffer and vice-versa
- to overcome the cursor data race condition, make them `atomic` instead of a simple data type and `static_assert(std::atomic<T>::is_always_lock_free);` on your platform before proceeding. See ss 4. Correcting the UB in the if-condition also enforces push and pop to not happend at the same time, 2 birds with one stone, nice!
- all built-in operations on the atomic data type carry sequentially consistent memory ordering. Which implies- after `store()`, we create a release semantics operation, similarly after `load()`, we create a aquire semantics operation.
- for atomic variables, if there is a contention between updating the value and reading the value, the update will happen before reading, hence new timeline will look like this. see ss 5
- False sharing- when you declare 2 member variables right next to each other (in code), they could be on the same cache line (L3 cache?) when they should not be. If your read and write thread are pinned to their own cores, they should each have their own cache line. If you wanna avoid this, use this C++20 feature, see ss 6. Adding a padding also helps. Kumar's comment: in this ss, I'm curious why the return type is `auto`. Note: the `empty()` function is declared `static`; and we are using the raw value of the `pushCursor` and `popCursor`, this is to avoid the possible slowness in some atomic operations
- In ss 7, he intentionally uses `std::memory_order_relaxed` and `std::memory_order_release` for `load()` and `store()` the `std::atomic` variables, these impose different constraints, lookup documentation. Note: we are not using pre-increment operation, we are doing `pushCursor + 1`
- In the 4th iteration of this design, see ss 8 & 9, we know that the push thread needs the true `popCursor` only when the buffer is full and similarly the pop thread needs the true `pushCursor` only when the buffer is empty, so we can work w/ cached push and pop cursors until then, each cached cursor stored locally to their own complementary threads (hence not atomic). Even though the cache pointers are local to the threads, we restrict false sharing by using the same technique.
- ss 10 and 11 shows and requirement where spsc comes in clutch. In this scenario, author says `memcpy` is expensive, so he reduces those operations by using a smart pointer and we get ss 12
- see benchmarking results in ss 13 and 14.
- Fifo4a is special- constraining the capacity to 2^N (N being an integer), and using the `&` operations to compute the index into to the array. Kumar's comment: the other versions of Fifo4 perform division, another solid example why you shouldn't perform division operations in critical sections, also pointed out by the presenter.

- Takeaway from the talk- knowing how to use `std::memory_order_relaxed`, `std::memory_order_acquire`, `std::memory_order_release`, etc, on your atomic data types and resolving false sharing can give a huge boost to your max. no. of operations/cycle. Presenter is confident that the boost in performance mostly comes from removing the false sharing. Take a look at the benchmark results.
