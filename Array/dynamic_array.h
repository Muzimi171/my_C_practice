#pragma once

#include <stddef.h>

typedef int Data;

typedef struct {
	Data* data;
	size_t size;
	size_t capacity;
}DynamicArray;

DynamicArray* create_array(size_t initial_capacity);

void destroy_array(DynamicArray* arr);

void array_append(DynamicArray* arr, Data value);

Data* array_read(DynamicArray* arr, size_t index);

int array_update(DynamicArray* arr, size_t index, Data value);

int array_insert(DynamicArray* arr, size_t index, Data value);

int array_delete(DynamicArray* arr, size_t index);

void print_array(const DynamicArray* arr);



