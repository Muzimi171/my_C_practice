#pragma once

#include <stddef.h> //为了使用size_t类型
#include <stdbool.h> //为了使用bool类型

//typedef 可以给结构体取别名
//定义一个学生结构体，包含学号和姓名
typedef struct {
	int id;
	char name[50];
} Student;

// 把Student类型定义为Data，方便后续使用
typedef Student Data;

typedef struct {
	Data* data; //指向结构体动态数组的指针，用于存储元素

	size_t size; //当前动态数组中元素的数量

	size_t capacity; //动态数组的总容量，即可以存储的最大元素数量
} DynamicArray;

// 创建并初始化一个动态数组
DynamicArray* create_array(size_t initial_capacity);

// 销毁动态数组
void destroy_array(DynamicArray* array);

// 在数组末尾添加元素,时间复杂度为O(1)，当需要扩容时，时间复杂度为O(n)
void array_append(DynamicArray* array, Data value);

// 访问指定下标的元素，返回指向该元素的指针，如果下标无效则返回NULL
Data* array_read(DynamicArray* array, size_t index);

// 更新指定下标的元素，返回true表示更新成功，false表示下标无效
bool array_update(DynamicArray* array, size_t index, Data value);

// 在指定下标插入元素，返回true表示插入成功，false表示下标无效
bool array_insert(DynamicArray* array, size_t index, Data value);

// 删除指定下标的元素，返回true表示删除成功，false表示下标无效
bool array_delete(DynamicArray* array, size_t index);

// 打印动态数组中的元素，print_func是一个函数指针，用于指定如何打印每个元素
void print_array(const DynamicArray* array , void (*print_func)(const void* data));
