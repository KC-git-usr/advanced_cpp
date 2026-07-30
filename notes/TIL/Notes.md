**constexpr notes**
- When you declare a variable as constexpr, you are indicating to the compiler that the value of the variable can be determined at compile time and will not change during the program's execution. This allows the compiler to replace the variable with its value wherever it is used in the code.
- You can also use constexpr with functions to declare that the function can be evaluated at compile time when called with constant expressions as arguments.
- Using constexpr appropriately can help improve performance, reduce runtime overhead, and enable some powerful compile-time optimizations in C++ code. However, keep in mind that not all operations can be evaluated at compile time, so not every variable or function can be declared as constexpr.
- Building in debug mode vs release mode makes a big difference! In other words, the compiler flags you pass to optimize your code changes the output binaries
- use constexpr for your constants in header files, if possible, otherwise const. And if you require the address of that constant to be the same everywhere mark it as inline.
__________________________________________________________________________________________

- **thread_local** : thread local storage duration specifier
- declaring a variable as such will give every thread created a copy of this variable and the data will not be shared across threads
- Reasons to use thread_local:
  - Maintaining Thread-Specific State
  - Thread-Specific Caching
- Caveat: more resource usage- since we're maintaining multiple copies and calling the c'tor and d'tor of the associated object every time a thread is created

__________________________________________________________________________________________

**shared libraries (.so) notes**

- a .so is a binary file containing compiled code and data that multiple programs can use simultaneously
- when you compile a program that uses shared libraries, the necessary functions and data from the shared library are not directly integrated into the executable file. Instead, the program's executable references the shared library's functions and data at runtime. This dynamic linking occurs when the program is loaded into memory, allowing the operating system to resolve and link the references to the shared library.
- advantages:
  - code reusability
  - reduced memory usage
  - easy updates and maintenance
  - faster program startup
  - version management
  - shared dependencies

**ros2 components and compositions**:

- typically ros2 nodes are executables (a single executable can have multiple nodes running in it)
- a component is our ros2 application compiled into a shared library instead of an executable and loaded at runtime by a container process
- from here we have 2 options with this shared library :
  - running multiple nodes in separate processes with the benefits of process/fault isolation as well as easier debugging of individual nodes
  - running multiple nodes in a single process with the lower overhead and optionally more efficient communication (leveraging advantages of Intra Process Comms)
- components are not in control of the controlling thread

__________________________________________________________________________________________

TIL: It is still possible to have memory leaks when using smart pointers, if you have circular references

Example code:
```
#include <memory>

class Node {
public:
std::shared_ptr<Node> next; // replace with weak_ptr to correct this issue

    Node() {
        std::cout << "Node constructed" << std::endl;
    }

    ~Node() {
        std::cout << "Node destructed" << std::endl;
    }
};

int main() {
  std::shared_ptr<Node> node1 = std::make_shared<Node>();
  std::shared_ptr<Node> node2 = std::make_shared<Node>();

  // Creating a circular reference
  node1->next = node2;
  node2->next = node1;

  // Both shared pointers still have a reference count of 1
  // No shared pointer has a reference count of 0, so the objects are not deleted
  return 0;
}
```
- Side note: In C++, **type erasure** is a technique used to hide the specific type of an object at runtime. This technique is often employed in smart pointers, including std::shared_ptr, to allow customization of certain behaviors, such as the deleter function, without exposing the exact type of the deleter to users of the smart pointer.
- I always wondered where type erasure really comes in clutch and this is a good example.

__________________________________________________________________________________________

TIL: Order of const: the const keyword applies to the type on its immediate left. If there's nothing on its left, it applies to the thing on its immediate right. Read from right to left when interpreting these declarations.
__________________________________________________________________________________________

**Universal reference notes**
- `T&&` is not always a rvalue reference
- Template Deduction Rules:
  - When T&& is used in a template, the type T can be deduced as either an lvalue reference, an rvalue reference, or a non-reference based on the argument passed during template instantiation.
  ```
  template <typename T>
  void bar(T&& x);  // x is a universal reference
  int i = 42;
  bar(i);    // T is deduced as int&; x is an lvalue reference
  bar(42);   // T is deduced as int; x is an rvalue reference
  bar(std::move(i)); // T is deduced as int&&; x is an rvalue reference(edited)
  ```
- Additional reading: https://isocpp.org/blog/2012/11/universal-references-in-c11-scott-meyers

__________________________________________________________________________________________

**`std::move()` vs `std::forward()` notes**
- `forward()` produces l-value references for l-value reference types, and r-value references for everything else.
  - The meaning is this: if the caller provided a named object, don’t move it, just reference it. If the caller provided an unnamed object, “move” it.
- Why would we need something like this? Don’t we (the programmer) know whether we are calling on an L-value or an R-value?
  - Not necessarily, if the function you are calling is a template.
- `std::forward()` is typically used for the universal reference. It passes along (or forwards) whatever the parameter reference type is. This prevents automatic decaying to L-value reference whenever the caller has passed down an R-value.
- don't use `std::move` when returning from a func. use it only for unique_ptrs and when copying is expensive (provided the src will no longer be used)
- The compiler is your friend and knows better. Also , because rvo. also because return std::move(foo); prevents rvo.
- https://stackoverflow.com/questions/12953127/what-are-copy-elision-and-return-value-optimization
- An rvalue reference can be treated as a lvalue (after the rvalue reference has been created). 
- This is key to understanding how `std::move` helps in moving ownership of dynamically alloc memory

__________________________________________________________________________________________

TIL: `nanosleep` is the preferred method to precisely time real-time loop when developing on the linux os. Source- $`man nanosleep` and by reading forums online

__________________________________________________________________________________________

TIL: In the context of programming a "sentinel" value (also referred to as a flag value, trip value, rogue value, signal value, or dummy data) is a special value in the context of an algorithm which uses its presence as a condition of termination, typically in a loop or recursive algorithm.

__________________________________________________________________________________________

Reference: [Scaling a Distributed Priority Queue to handle (dequeue) "10+ million items per minute"](https://engineering.fb.com/2021/02/22/production-engineering/foqs-scaling-a-distributed-priority-queue/)
- [Multitenancy architecture](https://en.wikipedia.org/wiki/Multitenancy): In my own words- this type of architecture is where 1 single server is serving to multiple clients via a load-balancer. So we have one resource (server) that is simultaneously shared by multiple clients each taking up some % of the server. Hence the analogy- multiple tenants (clients) 'occupying' the share resource.
- [Circuit Breaker pattern](https://learn.microsoft.com/en-us/azure/architecture/patterns/circuit-breaker): In my own words- this is a software fault recognition and handling mechanism. The circuit breaker acts as a proxy, between the client and server, and decides whether and when client requests should be reattempted, based on the monitored number of recent failures. Typically used to prevent an application from trying to invoke a remote, not local, service or access a shared resource if that operation is highly likely to fail.

__________________________________________________________________________________________

TIL: How `std::promise` works: 
- Imagine you make a promise to your friend that if his favorite team wins the championship you will give him $100. Friend says, alright bet, here's my PayPal number.
- You = thread #1.
- Friend = thread #2.
- promise = std::promise
- PayPal number = std::future
- "`std::promise` provides a facility to store a value or an exception that is later acquired asynchronously via a `std::future` object created by the `std::promise` object. Note that the `std::promise` object is meant to be used only once."
- Reference- https://en.cppreference.com/w/cpp/thread/promise

__________________________________________________________________________________________

TIL: the `final` specifier
- this specifier ensures that member functions cannot be overridden by child class member functions
- this specifier also helps in compiler devirtualization
  References- [link_1](https://en.cppreference.com/w/cpp/language/final) [link_2](https://marcofoco.com/blog/2016/10/03/the-power-of-devirtualization/)

The use case I see is preventing unintended inheritance- even though is see `virtual` or `override` idk if some child class is `override`-ing again (without reading more code). But if I see `final` specifier I can rest assured this is the final definition. Also hinting this is the final software architecture layer, especially in libraries.
I think, like many C++ features, you should treat the use of final as a design choice first and an optimization second

__________________________________________________________________________________________

TIL: if you have a nested templated struct, you can forward the typename of the outer struct simply by using the typename specifier in front of the inner struct
- For example:
```
/// \brief: Subscription encapsulation
template <class T>
struct SubscriptionWrapper {
  T msg{};
  rclcpp::MessageInfo msg_info{};
  // subscription handle
  typename rclcpp::Subscription<T>::SharedPtr subscription_handle_ptr{};
};

// instantiation
SubscriptionWrapper<internal_interface::dds_payload_type>
ecat_cmd_subscription_wrapper_;
```
```
SubscriptionWrapper is a nested templated struct
SubscriptionWrapper is the outer struct
rclcpp::Subscription<T>::SharedPtr is the inner struct
```

- Here's the other way of doing it:
```
template <class T>
struct SubscriptionWrapper {
  T msg{};

  template <class U>
  struct Inner {
      rclcpp::Subscription<U>::SharedPtr subscription_handle_ptr{};
      T msg_2{};
  };
};

// instantiation
SubscriptionWrapper<internal_interface::dds_payload_type>::Inner<internal_interface::dds_payload_type>
ecat_cmd_subscription_wrapper_;
```
- I personally don't think this is clean, if both T and U are of the same type

You don't need typename if the code doesn't try to reference SharedPtr. We need typename only if we need to reference a nested type (SharedPtr) within the dependent type (rclcpp::Subscription<T>), cause the compiler can't tell whether it's a type or a static member variable/function.
```
template <class T, template <class> class Handle>
struct HandleWrapper {
  using HandleT   = Handle<T>;
  using SharedPtr = typename HandleT::SharedPtr;
  
  T msg{};
  rclcpp::MessageInfo msg_info{};
  SharedPtr handle_ptr{};
};
```

__________________________________________________________________________________________

- Sometimes I declare a combination of c'tor and d'tor and the compiler throws some errors and I didn't completely understand why. This is a useful cheat-sheet to have
- Reference: https://howardhinnant.github.io/classdecl.html

__________________________________________________________________________________________
