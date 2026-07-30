Original source: https://www.youtube.com/watch?v=YokY6HzLkXs

# Notes:

- No inline necessary for templated functions
### `std::unique_ptr`:
- unique_ptr's are very useful for implementing RAII (Resource Acquisition Is Initialization)
```
void bar(HelperType&);
int foo(InputType input) {
// DON'T DO: std::unique_ptr<HelperType> owner{new HelperType(input)};
std::unique_ptr<HelperType> owner{std::make_unique<HelperType>(input)};
owner->calc();
bar(*owner);
// DON'T DO: bar(owner); and void bar(std::unique_ptr<HelperType> new_owner)
return owner->result();
}
```
```
std::unique_ptr<BarBase> create_bar(InputType);
class Foo {
std::unique_ptr<BarBase> owner;
public:
Foo(InputType input)
: owner(create_bar(input)) {}
~Foo() = default;
};
```
- `std::unique_ptr`'s are move only type, cannot be copied or copy assigned. Unique ownership can't be copied
- use move c'tor or move assignment c'tor to transfer ownership of `std::unique_ptr`'s using `std::move`, i.e.
  - `std::unique_ptr<Foo> a = std::make_unique<HelperType>(42);`
  - `std::unique_ptr<Foo> b{std::move(a)};`
  - OR `std::unique_ptr<Foo> b = std::move(a);`
- for transferring ownership to a func, pass the `unique_ptr` by value and return ownership from a func by returning by value

### `std::shared_ptr`:
- `std::shared_ptr`'s are copyable, if copied, # of owners_count increaments by 1
- if `std::move` or `=std::move`, then #owners_count remains the same
- when ownerships are being transfer, this is allowed: `std::unique_ptr` -> `std::shared_ptr`
- but this is not allowed: `std::shared_ptr` -> `std::unique_ptr`
- Speaker's recommendation: when you're starting to write code and aren't sure if you need `std::unique_ptr` or `std::shared_ptr`, start with `std::unique_ptr` as it's easy to now convert the source code to `std::shared_ptr`
- ownership is always shared equally, ownership cannot be forcefully given up or to claim unique ownership think of `std::shared_ptr`'s as shared owners of a unique state
- the first `std::shared_ptr` must be created using `std::make_shared<T>()` or `new`
- in multi-threaded env's `std::shared_ptr` does not provide any synchronization for the managed object. If not accounted for, it will lead to data race conditions. `std::shared_ptr` will synchronize access to the control block, but doesn't synchronize access to the pointed object itself

### Advanced usage:
### `std::weak_ptr`:
- non-owning reference to a `std::shared_ptr` managed object
- knows when the lifetime of the managed object ends
- a `std::weak_ptr` cannot be deferenced directly (but there's still a way, see ss), so technically it isn't a smart pointer
- `std::weak_ptr` is 'best' useful when the object is managed by a `std::shared_ptr`, not a `std::unique_ptr` or something else
- for example when caching, we can access (read only) the object while it's still alive
- `std::weak_ptr`'s help with a dangling reference problem

### custom deleters:
- if you're left with a C-style interface, where object initialization and destructions are done with explicit function calls, then custom delters will come to your rescue. For example: `fopen()` and `fclose()`
- (unfortunately) you have to create a `std::unique_ptr` with a custom deleter directly, instead of creating it with `std::make_shared`, since `std::make_shared` does not support custom deleters
- see ss on how to impleted custom deleter w/ `std::unique_ptr`. `std::unique_ptr` cannot type erase it's deleter, because it never allocates any memory on the heap
- custom deleters for `std::shared_ptr`'s are slightly different, see ss. The deleter is type erased, it is not part of the type, instead it's a template parameter on the c'tor. The deleter is copied over to other `std::shared_ptr`'s
