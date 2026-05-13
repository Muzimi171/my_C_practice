#include "dynamic_array.h"

#include <stdlib.h>
#include <stdio.h>


int main(void) {

    printf("--- 测试 Student 动态数组 ---\n");


    DynamicArray* array = create_array(2);

    array_append(array, 100);
    array_append(array, 200);
    array_append(array, 300);

    print_array(array);

    destroy_array(array);

    return 0;

}