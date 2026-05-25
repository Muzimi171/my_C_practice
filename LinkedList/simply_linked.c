#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
    int data;

    struct Node* next;
} Node;

// 创建一个新节点
Node* createNode(int data);

// 在链表尾部插入一个新节点， headRef是指向head指针的指针
// 在没有全局变量，没有返回值的情况下，我们使用多重指针来进行链表的插入和删除
void list_append(Node** headRef , int data);

// 在链表头部插入一个新节点
void prependNode(Node** headRef, int data);

// 打印链表，因为没有涉及到修改操作，所以不需要多重指针
void printList(Node* head);

// 查找链表里的指定节点
Node* findNode(Node* head, int data);

// 更新查找到的指定节点，与上面的findNode搭配使用
void updateNode(Node* head, int oldData, int newData);

// 删除链表中的指定节点，使用多重指针，直接操作head本体，而不是操作复制的副本，
// 因为对于复制的副本的操作，最后会随着函数的结束而被释放，导致无效操作
void deleteNode(Node** headRef, int data);

// 释放整个链表
// 释放操作也要用多重指数，直接操作head本体，防止悬挂指针
void list_free(Node** headRef);


int main(void)
{


}

Node* createNode(int data)
{


}

void list_append(Node** headRef , int data)
{


}

void prependNode(Node** headRef, int data)
{

    
}