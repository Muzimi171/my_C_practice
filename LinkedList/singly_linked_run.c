#include "singly_linked.h"

#include <stdio.h>
#include <stdlib.h>

// 如果Student结构体内的name字段是char*类型且由malloc分配，
// 那么还需要引入 <string.h>


// 我们自己定义的打印函数, 要符合print_singly_list函数中void (*print_func) (const void* data)的函数指针类型要求

void print_student(const void* data)
{
    const Student* student = (const Student*)data;

    printf("{ ID : %d , Name : %s , Age : %d }", student->id, student->name, student->age);
}

// 定义一个ID比较函数，比较标准是student->id与target->id是否相等
// 相等就返回1，不相等就返回0
// 并且函数本身的参数类型要符合find_singly_node函数中int (*compare_func) (const void* a, const void* b)的函数指针类型要求
int compare_student_id(const void* a, const void* b)
{
    const Student* student = (const Student*)a;

    const Student* target = (const Student*)b;

    // 三目运算符 , 相同返回1， 不相同返回0
    return (student->id == target->id) ? 1 : 0;
}

// 定义一个复杂的比较函数，比较标准是student->age与target->age是否相等
// 以及 student->name与target->name是否相等
// 只有当年龄和名字都相等时才返回1，否则返回0
int compare_student_id_and_age(const void* a, const void* b)
{
    const Student* student = (const Student*)a;

    const Student* target = (const Student*)b;

    return ((student->age == target->age) && (student->id == target->id)) ? 1 : 0;
}

// void free_student_name(void* data)
// 如果Student结构体内的name字段是char*类型且由malloc分配，
//那么我们还需要定义一个函数 free_student_name 来释放Student结构体内的name字段所占用的内存，避免内存泄漏, 然后再free整个节点。
// 但是在这个案例中Student结构体的name字段是一个固定长度的字符数组，所以不需要额外的内存释放操作，因此free_student_name函数在这个案例中可以直接省略掉，或者定义一个空函数来占位。

int main (void)
{
    Node* head = NULL;

    Student student[] = {
        {101, "Alice", 20},
        {102, "Marisa", 17},
        {103, "Cirno", 9},
        {104, "Sakuya", 25},
        {105, "Youkari", 17}
    };

    // 尾插法测试
    for (size_t i = 0; i < 5; i++)
    {
        append_singly_node(&head, student[i]);
    }

    printf("初始链表：\n");
    print_singly_list(head, print_student);

    // 头插法测试
    Student new_student = {100, "Reimu", 18};
    prepend_singly_node(&head, new_student);

    print_singly_list(head, print_student);


    // 查找测试
    printf("\n 查找ID为103的学生： \n");

    Student target_student = { 103, "target", 0};

    Node* found_node = find_singly_node(head, &target_student, compare_student_id);

    if (found_node)
    {
        printf("找到了！ID为103的学生信息是：\n");
        print_student(&(found_node->data));
        printf("\n");
    }
    else
    {
        printf("未找到该学生！\n");
    }

    printf("\n 查找ID为105且年龄为17岁的学生： \n");
   
    target_student.id = 105;
    target_student.age = 17;

    found_node = find_singly_node(head, &target_student, compare_student_id_and_age);

     if (found_node)
    {
        printf("找到了！ID为105且年龄为17岁的学生信息是：\n");
        print_student(&(found_node->data));
        printf("\n");
    }
    else
    {
        printf("未找到该学生！\n");
    }

    // 更新测试
    printf("\n 更新ID为100的学生姓名： \n");

    Student update_student = {100, "Koishi", 16};

    update_singly_node(head, &new_student, update_student, compare_student_id);

    print_singly_list(head, print_student);

    // 删除测试

    printf("\n 删除ID为102的学生： \n");
    Student delete_target = {102, "target", 0};
    delete_singly_node(&head, &delete_target, compare_student_id);

    print_singly_list(head, print_student);

    // 测试完毕，对链表进行释放
    free_singly_list(&head, NULL);

    return EXIT_SUCCESS;

}