# Smart pointers

Smart pointers are special pointers that automatically free the memory they manage under certain conditions.
By using smart pointers, one can avoid manually using `new` and `delete` in most cases, leading to a much safer memory management.
The two most useful types of smart pointers are **unique pointers** and **shared pointers**.


## Unique pointers

Unique pointers, (`std::unique_ptr<T>`) are very lightweight objects that:
* encapsulate a pointer;
* cannot be copied;
* free the memory when they are destroyed.

TODO: principe, perf


## Shared pointers

TODO
