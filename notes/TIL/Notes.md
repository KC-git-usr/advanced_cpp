TIL: the `final` specifier
- this specifier ensures that member functions cannot be overridden by child class member functions
- this specifier also helps in compiler devirtualization
References- [link_1](https://en.cppreference.com/w/cpp/language/final) [link_2](https://marcofoco.com/blog/2016/10/03/the-power-of-devirtualization/)

The use case I see is preventing unintended inheritance- even though is see `virtual` or `override` idk if some child class is `override`-ing again (without reading more code). But if I see `final` specifier I can rest assured this is the final definition. Also hinting this is the final software architecture layer, especially in libraries.
I think, like many C++ features, you should treat the use of final as a design choice first and an optimization second

__________________________________________________________________________________________
