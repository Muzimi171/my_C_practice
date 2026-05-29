#pragma once

#include <stddef.h> //为了使用size_t类型

// 建立一个学生结构体, 用于后面构建学生链表
typedef struct Student {
    int id;
    char name[50];
    int age;
} Student;

// 给Student类型起一个别名, 方便后续使用
typedef Student Data;

// 定义链表节点结构体
typedef struct Node {
    Data data;
    struct Node* next;
} Node;

// 创建一个新的节点
Node* create_singly_node(Data data);

// 在链表末尾添加一个节点
void append_singly_node(Node** headRef, Data data);

// 在链表首部插入一个节点，并更新头指针
// 因为会涉及到修改头指针，所以传入的是Node**类型的多重指针
void prepend_singly_node(Node** headRef, Data data);

// 打印整个链表，*print_func是一个函数指针，指向一个用于打印Data类型数据的函数
void print_singly_list(Node* head, void (*print_func) (const void* data));

// 查找链表中的指定节点
// 原案例中的函数还涉及到上下文指针的应用，但是在下实在没搞懂，所以就没写上。。。我自裁orz。。。。。
Node* find_singly_node(Node* head, const void* target_data, 
int (*compare_func) (const void* a, const void* b));

// 更新链表中的指定节点
void update_singly_node(Node* head, const void* target_data, Data newData, 
int (*compare_func) (const void* a, const void* b));

// 删除链表中的指定节点， compare_func是一个比较用的函数指针，
// 用来传递比较 节点数据(Node->data) 与 target_data 的函数
void delete_singly_node(Node** headRef, const void* target_data, 
int (*compare_func) (const void* a, const void* b));

// 释放整个链表，*free_data_func是一个函数指针，如果 Student 结构体内的 name 是 char* 类型且由 malloc 分配，就需要用到这个函数指针去释放 Student 结构体内的 name 字段所占用的内存，避免内存泄漏
// 此案例中Student结构体的name字段是一个固定长度的字符数组，所以不需要额外的内存释放操作，因此free_data_func参数在这个案例中可以传入NULL，或者直接不使用这个参数。
void free_singly_list(Node** headRef, void (*free_data_func)(void* data));

// 上面很多函数都配上一个函数指针，这是为了让这个链表具有更好的通用性，能够适用于不同类型的数据，而不仅仅是Student类型的数据。
//通过传入不同的函数指针，我们可以实现对不同类型数据的打印、比较和释放操作，从而使得这个链表能够适用于更广泛的场景，让这个链表具有更好的通用性和灵活性。