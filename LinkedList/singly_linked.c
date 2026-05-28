
#include <stdio.h>
#include <stdlib.h>

#include "singly_linked.h"

Node* createNode(Data data)
{
    Node* newNode = (Node*)malloc(sizeof(Node));

    if (newNode == NULL)
    {
        perror("节点内存分配失败！");
        return NULL;
    }

    newNode->data = data;
    newNode->next = NULL;

    return newNode;
}

void appendNode(Node** headRef, Data data)
{
    Node* newNode = createNode(data);

    // 节点的动态内存分配失败
    if (newNode == NULL)
    {
        return;
    }

    if (*headRef == NULL)
    {
        *headRef = newNode;
        return;
    }

    Node* lastNode = *headRef;

    while (lastNode->next != NULL)
    {
        lastNode = lastNode->next;
    }

    lastNode->next = newNode;
}

void prependNode(Node** headRef, Data data)
{
    Node* newNode = createNode(data);

    // 节点的动态内存分配失败
    if (newNode == NULL)
    {
        return;
    }

    newNode->next = *headRef;

    *headRef = newNode;
}

void printList(Node* head, void (*print_func) (const void* data))
{
    if (!head)
    {
        printf("链表为空！无法打印！\n");
        return;
    }

    if (!print_func)
    {
        printf("打印函数不存在，无法打印！\n");
        return;
    }

    printf("链表内容 ：");
    
    Node* current = head;

    while (current != NULL)
    {
        print_func(current);

        printf(" -> ");

        current = current->next;
    }

    printf(" NULL\n");

}

Node* findNode(Node* head, const void* target_data, 
int (*compare_func) (const void* a, const void* b))
{
    if (compare_func == NULL)
    {
        printf("错误：未提供比较函数. \n");

        return NULL;
    }

    Node* current = head;

    while (current != NULL)
    {
        // 两个数据相同则返回0
        if (compare_func(&(current->data), target_data) == 0)
        {
            return current;
        }

        current = current->next;
    }

    return NULL;
}


void updateNode(Node* head, const void* target_data, Data newData, 
int (*compare_func) (const void* a, const void* b))
{
    Node* targetNode = findNode(head, target_data, compare_func);

    if (targetNode == NULL)
    {
        printf("没有找到待更新节点！自动返回！\n");
        return;
    }

    targetNode->data = newData;

    printf("节点数据更新完毕！\n");
}


void deleteNode(Node** headRef, const void* target_data, 
int (*compare_func) (const void* a, const void* b))
{
    if ( !*headRef || !target_data || !compare_func)
    {
        printf("无效参数！无法进行删除操作！\n");

        return;
    }

    Node* current = *headRef;

    Node* prev = NULL; // 记录待删除节点的前一个节点，方便删除时建立连接

    // 比较函数，两个参数相同就返回0，此时的情况是头结点是待删除节点
    if (compare_func(&(current->data), target_data) == 0)
    {
        *headRef = current->next;
        
        free(current);

        printf("信息：头节点已经删除！\n");

        return;
    }

    // 只要不相等，就一直遍历下去，直到相等，或者curent == NULL
    while (current != NULL && compare_func(&current->data, target_data) != 0)
    {
        prev = current; // 跟踪current的前一个节点

        current = current->next;
    }

    // 直到遍历完整个链表也没有找到待删除节点
    if (current == NULL)
    {
        printf("没有找到待删除节点！自动返回！\n");
        return;
    }

    prev->next = current->next;

    free(current);

    printf("节点删除完毕！\n");

}


void freeList(Node** headRef, void (*free_data_func)(void* data))
{
    // 链表本来就是空的，直接返回
    if (*headRef == NULL)
    {
        return;
    }

    Node* current = *headRef;

    Node* nextNode = NULL;

    while (current != NULL)
    {
        nextNode = current->next;

        free_data_func(current);

        current = nextNode;
    }

    *headRef = NULL; // 链表释放完毕，给头结点指针赋NULL，防止悬挂指针

}

