#include <stdio.h>
#include <stdlib.h>
#include "doubly_linked.h"

int main(void)
{
	printf("创建一个空的链表...\n");

	DoublyLinkedList* playList = createList();

	if (!playList)
	{
		return 1;
	}

	printListForward(playList);

	printf("\n");

	printf("使用append函数给链表添加尾节点！\n");

	append(playList, (Song) {"Sinos De Natal", "Kand", 200 });
	append(playList, (Song) {"Forget Me Nots", "Patrice", 443 });
	append(playList, (Song) {"Never Stop", "Tanglang", 407 });
	append(playList, (Song) {"Blush", "Fusq", 243 });
	append(playList, (Song) {"Call Me Maybe", "CarlyRae" ,313 });

	printf("\n");


	printf("展示前后遍历！\n");

	printListForward(playList);
	printListBackward(playList);

	printf("\n");


	printf("展示插入功能!\n");

	printf("在歌曲《Call Me Maybe》的后面插入《DokiDoki》！\n");

	Node* findSongNode = findByTitle(playList, "Call Me Maybe");

	if (findSongNode)
	{
		insertAfter(playList, findSongNode, (Song) {"DokiDoki", "Salvato", 344 });

		printListForward(playList);
	}
	else
	{
		printf("没有找到Call Me Maybe 这首歌！\n");
	}

	printf("\n");


	printf("使用prepend函数给链表添加头结点！\n");

	prepend(playList, (Song) {"AIZO", "King Gnu", 335 });

	printListForward(playList);

	printf("\n");


	printf("演示删除操作！把歌曲《Call Me Maybe》在链表中删除！\n");

	Node* callMeMaybeNode = findByTitle(playList, "Call Me Maybe");

	if (callMeMaybeNode)
	{
		deleteNode(playList, callMeMaybeNode);

		printListForward(playList);
	}
	else
	{
		printf("没有找到Call Me Maybe 这首歌！\n");
	}

	printf("\n");


	printf("使用删除函数删除头结点！\n");

	Node* headNode = playList->head;
	  
	if (headNode)
	{
		deleteNode(playList, headNode);
		printListForward(playList);
	}

	printf("\n");


	printf("使用删除函数删除尾结点！\n");

	Node* tailNode = playList->tail;

	if (tailNode)
	{
		deleteNode(playList, tailNode);

		printListForward(playList);
	}

	printf("\n");


	printf("最后把整个链表释放掉！\n");

	freeList(playList);

	printf("链表内存已成功释放！\n");


	return EXIT_SUCCESS;



}