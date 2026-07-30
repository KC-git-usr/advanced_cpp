Original source: https://youtu.be/qCjEN5XRzHc?si=HbkXkE36I6COOjh6

# Notes:

### Performance:
- Don't do un-necessary work:
  - no unnecessary copying
  - no unnecessary allocations
- Use all computing power
  - use all cores
  - use SIMD
- Avoid waits and stalls
  - lockless data structs
  - async api's (don't wait/depend on other threads)
  - job system
- Use hardware efficiently
  - cache friendliness
  - well predictable code (branch prediction)
- OS-level efficiency
  - thread scheduling
- **Never start prematurely optimization (w/o profiling)**

### C++ code optimizations

- `constexpr`: if unsure whether a function can be made `constexpr` or not, just mark it and see if the compiler complains. "`constexpr` all the things"
- If an expression cannot be made `constexpr` try to make it `const`
- Marking a function as `noexcept` allows the compiler to make certain optimizations. It is especially **important** to mark move and move assignment c'tors as `noexcept`
- Use `static` for internal linkage. Nowadays, `inline` is a very weak hint to the compiler to optimize and has very little effect. It is useful in header only libraries to avoid ODR (One Definition Rule) evaluations, but it still doesn't help w/ performance. static will truly inline your machine code.
- C++ attributes: if your function never returns anything to the caller, then mark it as `[[noreturn]]` ; usually used for functions that terminate a program or throw exceptions. Use `[[likely]]` and `[[unlikely]]` for better branch prediction, this is a C++20 feature.
- Ways to pass function parameters: see ss

### Deep dive into Virtual Memory
- See ss

### Writing cache friendly code
- If memory is running low and there is contention, that's when we are swapping this working-set memory w/ SSD/HDD/etc memory. This leads to page faults, but the program won't crash, it takes a performance hit, hence this situation is a.k.a "thrashing". Always keep the working set small. See ss
- For extremely low latency, you need to
  - Pre-fetch memory adjacent to requested memory, this is called a cache line. Assumption: data locality
    - Examples of such containers: `std::array`, `std::vector`, `std::deque`, `std::flat_map`, `std::flat_set`. Also remember to access the elements in these containers sequentially.
    - Avoid these containers:  `std::list`, `std::set`, `std::unordered_set`, `std::map`, `std::unordered_map`. Because, these are pointer chasing data structs.
    - Case study: exploit concept of data locality in code- strategically ordering the members of a class for data locality. See ss. Essentially declare frequently used data members adjacent to each other, without any indirection . Store logic for infrequently used members indirectly using something like unique pointers using a pool allocator.
  - Cache- most recently used data is maintained on the high speed CPU die cache. Assumption: temporal locality- reuse memory recently used
    - Case study: exploit temporal locality in code- set thread affinity by pinning a thread to a specific core, prevent the OS from migrating a thread. Hence making it's L1 and L2 cache valid for longer. Set thread priority to reduce context switches.
    - Warning: incorrect exploitation of this technique can severely degrade OS performance. It better to start exploiting data locality first
- Summary on writing cache friendly code:
  - sequential memory access
  - use contiguous data structures
  - data oriented design
  - be intentional about using Structure Of Arrays(SOA) vs Array Of Structures (AOS)
  - Entity Component Systems <-- Kumar's comment: this is widely used in the gaming industry and for good reasons!
  - NUMA architectures

### Writing branch predictor friendly C++ code (in performance critical sections)
- Avoid in-directed calls (don't use virtual functions, function pointers, calls to dynamically shared libs, etc)
- Make branches predictable from an algorithm POV
- Remove branches themselves, executed both the branches and use math to choose one of the results. (This is how GPUs work underneath).
- Profile before making such optimizations

- Using a real-time tool like clang-tidy running on a clangd server, allows you to see difference performance related warnings in real-time while writing code. Get your performance metrics/tests in a CI/CD pipeline.

#### Enabling compiler optimizations:
- optimize for speed: GCC, LLVM, ICC use `-O2` or `-O3` flag
  - introduces longer compile time
- optimize for size: GCC, LLVM, ICC use `-Os` flag
- set target architecture: for GCC, LLVM, ICC
  - for x86: `-march=native -mtune=native`
  - for ARM: `-mcpu=native`
- use fast math:
  - GCC, LLVM: `-ffast-math` (included in `-Ofast`)
  - ICC: `-fp-mode=fast`
  - this optimization give you faster computation, but less precise results, and non-standard compliant

### Enable Link Time Optimization:
- GCC, LLVM: `-flto`
- ICC: `-ipo`
- this does optimizations like cross TU (translation unit) in-lining

### Use Unity Builds:
- cmake: `-DCMAKE_UNITY_BUILD=ON`
- essentially combines multiple source files into 1 unity source file, which is then compiled into an object file. This comes w/ many pros and cons

### Link Statically:
-  Static linking. Pro: can be optimized to a greater extent
- Dynamic linking. Pro: more space efficient (processor instruction capacity is in the order of KB), can be updated independently of executable

### Use Profile Guided Optimizations:
-  Idea: during building, the optimizers need to make a large number of guesses, based on heuristics. The optimizer needs this knowledge to generate instructions easier for the branch prediction. The advantage of this is we are using real-world data to make optimizations
- GCC, LLVM: `-fprofile-generate`. ICC: `-prof-gen`
- GCC, LLVM: `-fprofile-use`. ICC: `-prof-use`

-  **Lastly**- try different compilers, try different standard libraries, keep your tools updated. Try pre-loading your program w/ a replacement library (this is useful when you need a update a standard library function w/o changing the source code). Use binary post processing tools, such as LLVM bolt to produce a bolt optimized executable.
