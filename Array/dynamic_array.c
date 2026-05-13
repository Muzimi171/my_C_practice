#include "dynamic_array.h"

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#define INITIAL_CAPACITY 10

static int resize_array(DynamicArray* arr, size_t new_capacity)
{
	Data* new_arr = realloc(arr->data , new_capacity * sizeof(Data));

	if (new_arr == NULL)
	{
		perror("扩容失败");
		return -1;
	}

	arr->data = new_arr;
	arr->capacity = new_capacity;

	return 1;
}

DynamicArray* create_array(size_t initial_capacity)
{
	if (initial_capacity == 0)
	{
		initial_capacity = INITIAL_CAPACITY;
	}

	DynamicArray* arr = (DynamicArray*)malloc(sizeof(DynamicArray));

	if (arr == NULL)
	{
		perror("创建动态数组结构体失败！");
		return NULL;
	}

	arr->data = (Data*)malloc(sizeof(Data) * initial_capacity);

	if (arr->data == NULL)
	{
		free(arr);
		perror("创建动态数组失败！");
		return NULL;
	}

	arr->size = 0;
	arr->capacity = initial_capacity;

	return arr;
}

void destroy_array(DynamicArray* arr)
{
	if (arr)
	{
		free(arr->data);
		free(arr);
	}
}

void array_append(DynamicArray* arr, Data value)
{
	if (arr->size >= arr->capacity)
	{
		size_t new_capacity = arr->capacity * 2;
		resize_array(arr, new_capacity);
	}

	arr->data[arr->size] = value;

	arr->size++;
}

Data* array_read(DynamicArray* arr, size_t index)
{
	if (index >= arr->size)
	{
		printf("超出范围，无效访问\n");
		return NULL;
	}

	return &(arr->data[index]);
}

int array_update(DynamicArray* arr, size_t index, Data value)
{
	if (index >= arr->size)
	{
		printf("查出范围，无效更新\n");
		return -1;
	}

	arr->data[index] = value;

	return 1;
}

int array_insert(DynamicArray* arr, size_t index, Data value)
{
	if (index > arr->size)
	{
		printf("超出插入范围，无效操作\n");
		return -1;
	}

	if (arr->size >= arr->capacity)
	{
		size_t new_capacity = arr->capacity * 2;
		resize_array(arr, new_capacity);
	}

	for (size_t i = arr->size; i > index; i--)
	{
		arr->data[i] = arr->data[i - 1];
	}

	arr->data[index] = value;

	arr->size++;

	return 1;
}

int array_delete(DynamicArray* arr, size_t index)
{
	if (index >= arr->size)
	{
		printf("超出删除范围，无效操作！\n");
		return -1;
	}

	for (size_t i = index; i < arr->size - 1; i++)
	{
		arr->data[i] = arr->data[i + 1];
	}

	arr->size--;

	if (arr->size > 0 && arr->size <= arr->capacity / 4 && arr->capacity >= INITIAL_CAPACITY)
	{
		size_t new_capacity = arr->capacity / 2;

		// 保证缩容后的容量仍然能够装得下所有元素，并且不会小于初始容量

		if (new_capacity < arr->size)
		{

			new_capacity = arr->size;
		}

		if (new_capacity < INITIAL_CAPACITY)
		{

			new_capacity = INITIAL_CAPACITY;
		}

		printf("\n---> [缩容警告!] Size (%zu) <= Capacity/4 (%zu). 准备缩容至 %zu. \n",

			arr->size, arr->capacity / 4, new_capacity);

		resize_array(arr, new_capacity);
	}


	return 1;
}

void print_array(const DynamicArray* arr)
{
	printf("打印数组： Size（%zu） Capacity（%zu）\n", arr->size, arr->capacity);

	printf("[ ");

	for (int i = 0; i < arr->size; i++)
	{
		printf("%d ", arr->data[i]);
	}

	printf(" ]\n");
}


