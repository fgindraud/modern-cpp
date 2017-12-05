#Smart pointers

Smart pointers are special pointers that automatically free the memory they manage under certain conditions.
By using smart pointers, one can avoid manually using `new` and `delete` in most cases, leading to a much safer memory management.
The two most useful types of smart pointers are **unique pointers** and **shared pointers**.


## Unique pointers

Unique pointers, ([`std::unique_ptr<T>`](http://en.cppreference.com/w/cpp/memory/unique_ptr)) are very lightweight objects that:
* encapsulate a pointer;
* cannot be copied;
* free the memory when they are destroyed.

A unique pointer means "I am the only one responsible for managing this piece of memory".
Normal pointers can be created from a unique pointer but should never be freed.

Compared to a normal pointer, `std::unique_ptr<T>` has very little overhead (in particular, **no overhead on dereferencing**)
[Details](https://stackoverflow.com/questions/22295665/how-much-is-the-overhead-of-smart-pointers-compared-to-normal-pointers-in-c).

Motivating example: [motiv-unique.cpp](motiv-unique.cpp)

Minimal working example: [unique_ptr.cpp](unique_ptr.cpp)


## Shared pointers

Shared pointers ([`std::shared_ptr<T>`](http://en.cppreference.com/w/cpp/memory/shared_ptr))  are copyable smart pointers that
free the managed memory when the last copy of the pointer is destroyed.
They can be useful when managing shared resources or DAG-like structures.
Be careful though, they are more costly that unique pointers, in particular at creation and destruction
[Details](https://stackoverflow.com/questions/22295665/how-much-is-the-overhead-of-smart-pointers-compared-to-normal-pointers-in-c).

Example: [shared.cpp](shared.cpp)
