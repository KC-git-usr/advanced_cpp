- Original source: https://youtu.be/NH1Tta7purM?si=D480J2GcxBQa-b9t
- Presentation sides: https://github.com/CppCon/CppCon2017/blob/master/Presentations/When%20a%20Microsecond%20Is%20an%20Eternity/When%20a%20Microsecond%20Is%20an%20Eternity%20-%20Carl%20Cook%20-%20CppCon%202017.pdf


# Notes:

- If you know how to use measurement tools, you're already in the right path to writing high-performance C++ code. You don't need to be an expert in C++ techniques, it's all about measurement
- The "hotpath" or critical section is what matters in HFT, everything else is administrative work. The hotpath is typically 1% to 5% of the codebase
- The common factor between 2 threads on the same core is cache, disabling Intel's hyper-threading gives an instant code performance boost. Kumar's comment: lookup `alignas(std::hardware_destructive_interference_size) std::atomic<T> foo;` to prevent false sharing

- Slowpath removal
  - Avoid multiple if-else branches
```
if(checkForErrorA())
  handleErrorA();
else if(checkForErrorB())
  handleErrorB();
else if(checkForErrorC())
  handleErrorC();
else
  sendOrderToExchange();
```
  - Aim for this:
```
int64_t errorFlags;
...
if(!errorFlags)
  sendOrderToExchange();
else
  handleError(errorFlags);
```
  - Reasons: branch-prediction friendly and fewer instructions to execute


- Template-based configuration
  - Templated functions > virtual functions
  - Make use of factory functions, returning a `std::unique_ptr` object, to build the bridge between your compile type unknown (like a config file) and the concrete function implementation to be called.
  - See ss 1 and ss 2. Kumar's comment: there are multiple concepts being implemented here, also remember to brush up your template deduction rules- link_1 link_2
- Lambda functions are convenient
  - lambdas actually improve human code reading time
  - lambda function calls get automatically inlined by compiler (most likely)
- Exceptions in C++
  - Presenter claims exceptions are zero cost as long as they don't throw or if you don't drop into them
- `__attribute__((noinline))` and `__attribute__((inline))` are strong hints to the compiler. Make sure to measure or look at the assembly code.
- Keeping the cache hot and ready for execution (in HFT)
  - typically the cache is trampled by non-hotpath data/instructions
  - simple solution: run a very frequent dummy path through your entire system, keeping both your data cache and instruction cache primed
  - See ss 3
- Avoid system calls, cause you want to get rid of all kernel interrupts

- Profiling: examining what your code is doing (bottlenecks in particular). Benchmarking: timing the speed of your system.
- Presenter does not like to use these tools for measurement of low latency systems that has micro-optimized code: gprof, callgrind, google benchmark, etc. He still claims they useful in their own right, just not for this scenario. Presenter prefers a physical replica of the system that has the exact hardware (servers and network switches) of your production system- a unique kind of CI/CD, and measuring the in-out timestamps.
- Be careful with profile guided optimization- if you're constantly optimizing for hotpath latency, your system may not be stable in certain scenarios or you may also be overfitting.

- Kumar's TLDR: the talk is on a VERY niche field. Other than the notes above and what I've already come across in many other talks, I didn't find much relevant information from this talk.
