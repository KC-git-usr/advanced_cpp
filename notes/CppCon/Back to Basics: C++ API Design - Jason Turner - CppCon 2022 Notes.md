Original source: https://www.youtube.com/watch?v=zL-vn_pGGgY

# Notes:

- Use `[[nodiscard]]` and noexcept appropriately
  - `[[nodiscard]]` can be used in junction with a custom data type too, so that any function returning this custom data type need not explicitly state `[[nodiscard]]` 
  - All non-mutating functions (getters/accessors/const) should use `[[nodiscard]]` 
  - Kumar's comment: Personally, I don't like `[[nodiscard]]` cause it clutters code
- Be intentional about using a verb vs adjective when naming functions
- Something that is moved (using `std::move`) should being in a valid by un-specified state <-- you enforce this force by defining a custom move c'tor
---------------------------
Designing the api for a facotry function:
```
Widget *make_widget(int widget_type);
```
Few things that can be improved with the above api:
- we don't know if:
  - it could be a reference to a "thing"
    - "thing" = is a static holder of all the widgets that have been created so far,
    - "thing" = could be look-up into a singleton
  - it could be something newly created on the heap
- never return a raw pointer, use a smart pointer
  - Example code:
  ```
      FILE *fopen(const char* pathname, const char* mode);
      // after rewriting
      using FilePtr = std::unique_ptr<FILE, decltype([](FILE *f) { flclose(f); })>;
      FilePtr fopen(const std::filesystem::path& path, const std::string& mode);
      // OR
      FilePtr fopen(const std::filesystem::path& path, std::string_view mode);
  ```
---------------------------
- Prefer `std::string_view` (C++17) over `std::string` when you need a read-only string, especially for function parameters.
---------------------------
- Be wary of implicit conversions! Avoid this by using strong types
- When you absolutely cannot allow implicit conversions, here's how you can enforce this:
  - if you `=delete` a template, it will become the match for any non-exact parameters, and prevent implicit conversions
  - this trick must be used sparingly
---------------------------
- Don't pass smart pointers unless you need to participate in the lifetime <- I didn't understand this, he skipped this slide
  - only to be used for single/optional objects

"Participating in the Lifetime":
- The guideline suggests that you should pass smart pointers to a function only when that function needs to participate in the management of the object's lifetime.
- If the function does not need to take ownership or extend the lifetime of the object, prefer passing raw pointers or references
- When you pass a smart pointer as a function parameter, you are essentially sharing the ownership of the pointed object with the function. By following this guideline, you make the ownership semantics clear. Functions that take smart pointers are explicitly stating their intention to participate in the object's ownership.
