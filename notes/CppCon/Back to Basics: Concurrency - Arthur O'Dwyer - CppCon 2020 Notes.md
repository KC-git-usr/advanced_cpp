Original source: https://youtu.be/F6Ipn7gCOsY?si=tm49aF2mxmKO5FmI
Slide deck: https://github.com/CppCon/CppCon2020/blob/main/Presentations/back_to_basics_concurrency/back_to_basics_concurrency__arthur_odwyer__cppcon_2020.pdf

# Notes

- Logical synchronization:
  - Don't busy wait (don't use while loops checking atomic flags)
  - Use `std::scoped_lock`
  - Use `std::condition_variable` for "wait until" or to wake up and notify one/all thread/s that is blocked on this variable type <- this is a way to implement a non-busy wait. See ss 1 and 2
  - Use `std::promise`/`std::future` . Which still uses a mutex + condition variable internally
  - If you need a code block to strictly be executed only once, consider  `std::once_flag` <- when you want a singleton per instance of some object. See ss 3
  - C++17 now has `std::shared_mutex` (it's read/write lock)
  - If you have a case where you have a global config that multiple threads use, but don't wish to protect it with a mutex, then consider the "blue-green" pattern. TLDR: make a private copy of the global config, make your change, then perform an atomic exchange of the copy with the original. See ss 4, 5 and 6
  - Prefer higher level frameworks if your application is fundamentally multi-threaded in nature- promise/future, coroutines, ASIO, etc. The above recommendations are for one-off occurrences. 
