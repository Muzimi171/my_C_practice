#define _CRT_SECURE_NO_WARNINGS
#include "DoublyLinked.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static Node* _createNode(Song songdata)
{
	Node* newNode = (Node*)malloc(sizeof(Node));

	if (newNode == NULL)
	{
		perror("节点动态内存分配失败！");
		return NULL;
	}

	newNode->data.artist = (char*)malloc(strlen(songdata.artist) + 1);

	if (newNode->data.artist == NULL)
	{
		perror("分配动态内存失败！");
		free(newNode);
		return NULL;
	}

	newNode->data.title = (char*)malloc(strlen(songdata.title) + 1);

	if (newNode->data.title == NULL)
	{
		perror("分配动态内存失败！");
		free(newNode->data.artist);
		free(newNode);
		return NULL;
	}

	strcpy(newNode->data.title , songdata.title);
	strcpy(newNode->data.artist, songdata.artist);

	newNode->data.duration = songdata.duration;

	newNode->next = NULL;

	newNode->prev = NULL;

	return newNode;
}

DoublyLinkedList* createList()
{
	DoublyLinkedList* list = (DoublyLinkedList*)malloc(sizeof(DoublyLinkedList));

	if (list == NULL)
	{
		perror("分配内存失败！");
		return NULL;
	}

	list->head = NULL;
	list->tail = NULL;
	list->size = 0;

	return list;
}

void freeList(DoublyLinkedList* list)
{
	if (!list)
	{
		perror("List is NULL, nothing to free.\n");

		return;
	}

	Node* current = list->head;

	while (current != NULL)
	{
		Node* nextNode = current->next;
		free(current->data.artist);
		free(current->data.title);
		free(current);
		current = nextNode;
	}

	free(list);
}

bool append(DoublyLinkedList* list, Song songData)
{

	if (!list)
	{
		perror("List is NULL, cannot append.");

		return false;
	}

	Node* newNode = _createNode(songData);

	if (!newNode)
	{
		return false;
	}

	if (list->head == NULL)
	{
		list->head = newNode;
		list->tail = newNode;
	}
	else
	{
		list->tail->next = newNode;
		newNode->prev = list->tail;
		list->tail = newNode;
	}

	list->size++;

	return true;
}

bool prepend(DoublyLinkedList* list, Song songData)
{
	if (!list)
	{
		perror("List is NULL, cannot prepend.");

		return false;
	}

	Node* newNode = _createNode(songData);

	if (newNode == NULL)
	{
		return false;
	}

	if (list->head == NULL)
	{
		list->head = newNode;
		list->tail = newNode;
	}
	else
	{
		newNode->next = list->head;
		list->head->prev = newNode;
		list->head = newNode;
	}

	list->size++;

	return true;
}

bool insertAfter(DoublyLinkedList* list, Node* targetNode, Song songData)
{
	if (!list || !targetNode)
	{
		perror("链表或者节点不存在，无法插入！");
		return false;
	}

	Node* newNode = _createNode(songData);

	if (!newNode)
	{
		return false;
	}

	newNode->next = targetNode->next;
	newNode->prev = targetNode;

	if (targetNode->next != NULL)
	{
		targetNode->next->prev = newNode;
	}
	else
	{
		list->tail = newNode;
	}

	targetNode->next = newNode;

	list->size++;

	return true;
}

bool deleteNode(DoublyLinkedList* list, Node* nodeToDelete)
{
	if (!list || !nodeToDelete)
	{
		perror("链表或者待删除节点不存在！");
		return false;
	}

	if (nodeToDelete->prev != NULL)
	{
		nodeToDelete->prev->next = nodeToDelete->next;
	}
	else
	{
		list->head = nodeToDelete->next;
	}

	if (nodeToDelete->next != NULL)
	{
		nodeToDelete->next->prev = nodeToDelete->prev;
	}
	else
	{
		list->tail = nodeToDelete->prev;
	}

	free(nodeToDelete->data.artist);
	free(nodeToDelete->data.title);
	free(nodeToDelete);

	list->size--;

	return true;
}

Node* findByTitle(const DoublyLinkedList* list, const char* title)
{
	if (!list)
	{
		perror("链表不存在！");
		return NULL;
	}

	Node* current = list->head;

	while (current != NULL)
	{
		if (strcmp(current->data.title, title) == 0)
		{
			return current;
		}

		current = current->next;
	}

	printf("没有找到该节点！返回NULL！\n");
	return NULL;
}

void printListForward(const DoublyLinkedList* list)
{
	if (!list || !list->head)
	{
		perror("链表为空！");
		return;
	}

	Node* current = list->head;

	int index = 1;

	printf("正向打印链表内容：\n ");

	while (current != NULL)
	{
		printf("No.%d {%s , %s, %d } \n", index++, current->data.title, current->data.artist,current->data.duration);

		current = current->next;
	}

	printf("---打印完毕---\n");
}

void printListBackward(const DoublyLinkedList* list)
{
	if (!list || !list->head)
	{
		perror("链表为空！");
		return;
	}

	Node* current = list->tail;

	int index = list->size;

	printf("反向打印链表内容: \n");

	while (current != NULL)
	{
		printf("No.%d {%s, %s, %d } \n", index--, current->data.title, current->data.artist,current->data.duration);

		current = current->prev;
	}

	printf("---打印完毕---\n");
}





