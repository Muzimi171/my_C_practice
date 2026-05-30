#pragma once

#include <stddef.h> 
#include <stdbool.h>

// 用双向链表实现一个歌曲播放列表（歌单）

// 链表节点要存储的value ： 一个Song结构体
// 包含着歌曲的名字，歌手，时长
typedef struct Song{
	char* title;

	char* artist;

	int duration;
} Song;

// 给Song结构体起一个别名，叫Data，方便后续使用
typedef struct Song Data;

// 双向链表的节点， 包含三个要素：
// 1. 存储信息的Data
// 2. 指向前一个节点的指针prev
// 3. 指向后一个节点的指针next
typedef struct Node {
	Data* song;
	
	struct Node* prev;

	struct Node* next;
} Node; 

// 单向链表只有一个head锚点，但是双向链表有两个锚点：head和tail
// 所以为了方便管理，我们定义一个DoublyLinkedList结构体，包含三个要素：
// 1. head指针，指向链表的第一个节点
// 2. tail指针，指向链表的最后一个节点
// 3. size变量，记录链表中节点的数量
typedef struct DoublyLinkedList {
	Node* head;
	
	Node* tail;

	int size;
} DoublyLinkedList;


// 创建一个空白的双向链表
DoublyLinkedList* createList();

// 释放双向链表
void freeList(DoublyLinkedList* list);

// 在链表末尾添加一个新的节点，存储给定的歌曲信息
// 成功返回true，失败返回false（例如内存分配失败），下面同理
bool append(DoublyLinkedList* list, Data songData);

// 在链表开头添加一个新的节点，存储给定的歌曲信息
bool prepend(DoublyLinkedList* list, Data songData);

// 根据歌曲标题在链表中查找节点，返回指向该节点的指针，如果没有找到则返回NULL
Node* findByTitle(const DoublyLinkedList* list, const char* title);

// 在链表的指定节点targetNode后面插入一个新的节点，存储给定的歌曲信息
bool insertAfter(DoublyLinkedList* list, Node* targetNode, Data songData);

// 删除指定节点
bool deleteNode(DoublyLinkedList* list, Node* targetNode);

// 打印链表中的所有歌曲信息（正向打印）
void printListForward(DoublyLinkedList* list);

// 打印链表中的所有歌曲信息（反向打印）
void printListBackward(DoublyLinkedList* list);