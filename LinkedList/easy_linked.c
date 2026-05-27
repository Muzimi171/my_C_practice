#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
    int data;

    struct Node* next;
} Node;

// 创建一个新节点
Node* create_node(int data);

// 在链表尾部插入一个新节点， headRef是指向head指针的指针
// 在没有全局变量，没有返回值的情况下，凡是涉及到head指针的改动，我们使用多重指针，
// 直接操作head本体，而不是操作复制的副本，因为对于复制的副本的操作，最后会随着函数的结束而被释放，导致无效操作
void list_append(Node** headRef , int data);

// 在链表头部插入一个新节点，涉及到对头指针head的修改，使用多重指针
void list_prepend(Node** headRef, int data);

// 打印链表，因为没有涉及到修改操作，所以不需要多重指针
void list_print(Node* head);

// 查找链表里的指定节点
Node* find_list_node(Node* head, int data);

// 在目标节点的后面插入一个新节点，一般用于在中间插入
void insert_list_node(Node** headRef, int targetData , int insert_data);

// 更新查找到的指定节点，与上面的find_list_node搭配使用
void update_list_node(Node* head, int oldData, int newData);

// 删除链表中的指定节点，因为会有删除头结点的可能，所以使用多重指针，直接操作head本体，而不是操作复制的副本，
// 因为对于复制的副本的操作，最后会随着函数的结束而被释放，导致无效操作
void delete_node(Node** headRef, int data);

// 释放整个链表
// 释放操作也要用多重指数，直接操作head本体，防止悬挂指针
void list_free(Node** headRef);


int main(void)
{
    Node* head = NULL;

    // 尾插法测试
    list_append(&head, 100);
    list_append(&head, 200);
    list_append(&head, 300);

    list_print(head);

    // 头插法测试
    list_prepend(&head, 0);

    list_print(head);

    // 中间插入测试,在200后面插入250
    insert_list_node(&head, 200, 250);

    // 更新节点测试
    update_list_node(head, 300, 290);
    
    list_print(head);

    // 删除测试
    delete_node(&head, 0);

    // 测试完毕，释放链表
    list_free(&head);

    return EXIT_SUCCESS;

}

Node* create_node(int data)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    
    if (newNode == NULL)
    {
        perror("创建节点失败：内存分配失败");

        return NULL;
    }

    newNode->data = data;

    newNode->next = NULL;

    return newNode;
}

void list_append(Node** headRef , int data)
{
    Node* newNode = create_node(data);

    // 卫语句
    if (newNode == NULL)
    {
        return;
    }

    if (*headRef == NULL)
    {
        *headRef = newNode;
        return;
    }

    Node* temp = *headRef;

    while (temp->next != NULL)
    {
        temp = temp->next;
    }

    temp->next = newNode;

}

void list_prepend(Node** headRef, int data)
{
    Node* newNode = create_node(data);

    newNode->next = *headRef;

    *headRef = newNode;
}

void list_print(Node* head)
{
    Node* current = head;

    printf("当前列表 : ");

    while (current != NULL)
    {
        printf("%d => ", current->data);

        current = current->next;
    }

    printf("NULL\n");
}


Node* find_list_node(Node* head, int data)
{
    Node* current = head;

    if (current == NULL)
    {
        printf("链表为空，无法查找！\n");
        return NULL;
    }

    while (current != NULL)
    {
        if (current->data == data)
        {
            return current;
        }

        current = current->next;
    }

    printf("没有找到目标节点！\n");

    return NULL;
}

void insert_list_node(Node** headRef, int targetData , int insert_data)
{
    Node* insert_node = create_node(insert_data);

    if (*headRef == NULL)
    {
        *headRef = insert_node;
        return;
    }

    Node* targetNode = find_list_node(*headRef , targetData);

    if (targetNode == NULL)
    {
        printf("没有找到插入位置！自动返回！\n");
        return;
    }

    insert_node->next = targetNode->next;
    targetNode->next = insert_node;
}

void update_list_node(Node* head, int oldData, int newData)
{
    Node* target_node = find_list_node(head, oldData);

    if(target_node != NULL)
    {
        target_node->data = newData;

        printf("数据 %d 已经成功更新至 %d. \n", oldData, newData);
    }
    else
    {
        printf("待修改节点未找到!\n");
    }
}

void delete_node(Node** headRef, int data)
{
    Node* temp = *headRef;

    Node* prev = NULL;

    // 链表不为NULL时，被删除的节点是head节点的情况
    if (temp != NULL && temp->data == data)
    {
        *headRef = temp->next;
        free(temp);
        return;
    }

    // 只要temp不为空并且没找到待删除节点，就一直循环下去
    while (temp != NULL && temp->data != data)
    {
        // prev复制跟踪temp的前一个节点，方便删除temp
        prev = temp;

        temp = temp->next;
    }

    // 遍历完整个链表也没有找到待删除节点
    if (temp == NULL)
    {
        printf("没有找到待删除节点，自动返回\n");
        return;
    }

    prev->next = temp->next;

    free(temp);
}

void list_free(Node** headRef)
{
    if (*headRef == NULL)
    {
        printf("链表为空，直接返回\n");
    }

    Node* current = *headRef;
    Node* next_node = NULL;

    while (current != NULL)
    {
        next_node = current->next;
        free(current);
        current = next_node;
    }

    // 链表释放完毕，给头结点指针赋NULL，防止悬挂指针
    *headRef = NULL;
}