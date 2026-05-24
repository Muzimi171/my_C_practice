#include "dynamic_array.h"

#include <stdio.h> //为了使用printf函数
#include <stdlib.h> //为了使用malloc,realloc,free函数

#define INITIAL_CAPACITY 10 //默认初始容量

// 静态内部函数，用来给动态数组进行扩容和缩容操作
static bool resize_array(DynamicArray* array, size_t new_capacity)
{
	// 使用realloc重置动态数组的容量
	Data* new_array = realloc(array->data, new_capacity);

	if (new_array == NULL)
	{
		perror("重置动态数组容量失败！");
		return false;
	}

	array->data = new_array;
	array->capacity = new_capacity;

	return true;
}

DynamicArray* create_array(size_t initial_capacity)
{
	if (initial_capacity == 0)
	{
		initial_capacity = INITIAL_CAPACITY;
	}

	DynamicArray* array = (DynamicArray*)malloc(sizeof(DynamicArray));

	if (array == NULL)
	{
		perror("申请DynamicArray结构体动态内存失败!");
		return NULL;
	}

	array->data = (Data*)malloc(initial_capacity * sizeof(Data));

	if (array->data == NULL)
	{
		perror("申请array->data数组动态内存失败!");
		free(array);
		return NULL;
	}

	array->size = 0;
	array->capacity = initial_capacity;

	return array;
}

void destroy_array(DynamicArray* array)
{
	if (array && array->data)
	{
		//释放，并防止悬挂指针
		free(array->data);
		array->data = NULL;

		free(array);
		array = NULL;
	}
}

void array_append(DynamicArray* array, Data value)
{
	// 当动态数组已满时继续插入，会触发扩容操作
	if (array->size == array->capacity)
	{
		printf("当前动态数组已满,检测到array_append操作,开始扩容\n");
		size_t new_capacity = array->capacity * 2;
		resize_array(array, new_capacity);
	}

	//后缀递增，先用后加，每次尾部插入之后，size会自己更新
	array->data[array->size++] = value;

}

Data* array_read(DynamicArray* array, size_t index)
{
	if (index >= array->size)
	{
		perror("超出索引范围，无效访问");
		return NULL;
	}

	// 返回查找到的元素的地址
	return &(array->data[index]);
}

bool array_update(DynamicArray* array, size_t index, Data value)
{
	if (index >= array->size)
	{
		perror("超出索引范围，无效访问");
		return false;
	}

	array->data[index] = value;

	return true;
}

bool array_insert(DynamicArray* array, size_t index, Data value)
{
	// 动漫数组已满继续插入，触发扩容操作
	if (array->size == array->capacity)
	{
		printf("当前动态数组已满,检测到array_insert操作,开始扩容\n");
		size_t new_capacity = array->capacity * 2;
		resize_array(array, new_capacity);
	}

	// 有扩容操作，所以在数组已满并触发扩容操作之后，
	// 可以在 array->size 的位置进行插入
	if (index > array->size)
	{
		perror("超出插入范围! 无效插入!");
		return false;
	}

	// 从末尾开始，把元素一个一个往后挪，给待插入的元素留出空间
	for (size_t i = array->size; i > index; i--)
	{
		array->data[i] = array->data[i - 1];
	}

	array->data[index] = value;

	//更新元素数目
	array->size++;

	return true;
}

bool array_delete(DynamicArray* array, size_t index)
{
	if (index >= array->size)
	{
		perror("超出删除范围，无效删除！");
		return false;
	}

	// 因为删除了元素，所以后面的元素要一个一个往前挪
	for (size_t i = index; i < array->size-1 ; i++)
	{
		array->data[i] = array->data[i + 1];
	}

	// 更新元素数目
	array->size--;

	// 当size = Capacity/4 时，触发扩容，capcity变为原来的二分之一
	// 并且只有当Capacity大于默认初始容量INITIAL_CAPACITY时才能触发，
	// 防止频繁的触发扩容和缩容，造成性能的损耗
	if (array->size > 0 && array->size <= array->capacity/4 && array->capacity >= INITIAL_CAPACITY)
	{
		size_t new_capacity = array->capacity / 2;

		// 防止缩容后容量不够（虽然我觉得不太必要）
		if (new_capacity < array->size)
		{
			new_capacity = array->size;
		}

		// 防止频繁触发扩容和缩容操作
		if (new_capacity < INITIAL_CAPACITY)
		{
			new_capacity = INITIAL_CAPACITY;
		}

		printf("\n检测到Size: %zu  , Capacity: %zu, Size <= Capacity/4: %zu , Capacity 缩容为原来的二分之一: %zu\n", array->size, array->capacity, array->capacity/4, new_capacity);

		resize_array(array , new_capacity);
		
	}

	return true;

}

// *print_func是一个回调函数，用来传入 返回值是void， 参数是 const void* 类型的函数
void print_array(const DynamicArray* array , void (*print_func)(const void* data))
{
	if (!print_func)
	{
		printf("错误：没有提供打印函数！\n");

		return;
	}

	printf("Array (Size : %zu, Capacity : %zu) : \n", array->size, array->capacity);

	for (size_t i = 0; i < array->size; i++)
	{
		print_func(&array->data[i]);

		printf("   ");
		
	}

	printf("\n\n");
	
}