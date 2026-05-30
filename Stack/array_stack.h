#pragma once // 可以让编译器在编译过程中只包含一次该头文件

#include <stddef.h> // 包含 size_t 类型的定义
#include <stdbool.h> // 包含 bool 类型的定义

// 我们先给struct Stack取个别名，这样在定义函数时就可以直接使用 Stack* 来表示指向栈的指针，而不需要每次都写 struct Stack*。
typedef struct Stack Stack;

// 至于Stack结构体具体的实现，我们放在源文件中定义，这样用户在使用这个栈的时候就不需要关心它的内部细节了。这也是一种封装的方式，可以隐藏实现细节，提高代码的安全性和可维护性。原理就是我们在头文件中只声明了 Stack 结构体的存在，而没有定义它的内容，这样用户就无法直接访问它的成员，只能通过我们提供的接口函数来操作栈，从而实现了数据隐藏和封装。


Stack* stack_create(size_t capacity, size_t element_size);