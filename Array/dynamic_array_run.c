#include <stdio.h>
#include <stdlib.h>

#include "dynamic_array.h"

// 根据要打印的动态数组的数据类型，定义我们自己的回调函数
// 因为是Student类型，所以
void print_student(const void* data)
{
    // 使用强制换行，把地址转换成const Student类型
    const Student* student_element = (const Student*)data;

    printf("Student : {%d , %s} ", student_element->id, student_element->name);
}

int main(void)
{
    printf("-----测试Student动态数组----- \n");

    DynamicArray* student_list = create_array(5);

    Student s1 = {1, "Sakuya"};
    Student s2 = {2, "Marisa"};
    Student s3 = {3, "Flandre"};

    // 连续在动态数组里添加三个学生
    array_append(student_list, s1);
    array_append(student_list, s2);
    array_append(student_list, s3);

    print_array(student_list, print_student);

    Student s4 = {4, "Aya"};
    Student s5 = {5, "Satori"};

    // 在索引1插入一个新学生，并更新索引0学生的信息
    array_insert(student_list, 1, s4);
    array_update(student_list, 0, s5);

    print_array(student_list, print_student);

    Student s6 = {6, "Koishi"};
    Student s7 = {7, "Youmu"};
    Student s8 = {8, "Remilia"};

    //连续添加，查看扩容效果
    array_append(student_list, s6);
    array_append(student_list, s7);
    array_append(student_list, s8);

    print_array(student_list, print_student);


    //连续删除，查看缩容效果
    array_delete(student_list, 0);
    array_delete(student_list, 0);
    array_delete(student_list, 0);
    array_delete(student_list, 0);
    array_delete(student_list, 0);

    print_array(student_list, print_student);

    // 读取指定下标的学生信息
    Student* read_student = array_read(student_list, 0);

    printf("读取的学生信息：Student : { %d, %s}", read_student->id, read_student->name);

    // 测试结束，对动态数组进行释放
    destroy_array(student_list);

    return EXIT_SUCCESS;
}