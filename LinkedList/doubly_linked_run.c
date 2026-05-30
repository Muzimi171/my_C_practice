#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "doubly_linked.h"


int main() {

    printf("基于双向链表实现的歌曲播放列表（歌单）演示\n");

    // 1. 创建一个空的播放列表
    DoublyLinkedList* playlist = createList();

    if (!playlist) {

        // 内存分配失败，无法创建播放列表
        return EXIT_FAILURE; 

    }

    printf("\n");

    // 2. 添加初始歌曲 (Append)
    printf("请把你的喜欢的歌曲添加到歌单里吧！\n");

    append(playlist, (Data) { "Peeping Tom", "Jamie Berry", 167 });
    append(playlist, (Data) { "Checklist", "MAX", 203 });
    append(playlist, (Data) { "Billie Jean", "Michael Jackson", 178 });
    append(playlist, (Data) { "Sinos De Natal", "Mashup", 200 });

    printListForward(playlist);

    printf("\n");



    // 3. 演示向前和向后遍历
    printf("演示向前和向后遍历:\n");

    printListForward(playlist);

    printf("\n");

    printListBackward(playlist);

    printf("\n");



    // 4. 演示插入操作 (Insert After)
    printf("在 《Checklist》 之后插入新歌曲: 《5:20AM》\n");
   
    Node* targetNode = findByTitle(playlist, "Checklist");

     printf("这个操作的时间复杂度是O(1)，因为我们已经通过findByTitle函数找到了目标节点，不需要再去遍历链表了\n");

    if (targetNode) 
    {

        insertAfter(playlist, targetNode, (Data) { "5:20AM", "Dao",  520});

        printListForward(playlist);

    }
    else {

        printf("没有找到 《Checklist》 这首歌，无法进行插入操作！\n");
    }

    printf("\n");

    // 5. 演示在头部插入 (Prepend)
    printf("把 《First Class》这首歌插入到歌单的开头。\n");

     printf("这个操作的时间复杂度是O(1)，因为我们直接在链表头部插入新节点，不需要遍历链表了\n");

    prepend(playlist, (Data) { "First Class", "Jack Harlow", 174 });

    printListForward(playlist);

    printf("\n");



    // 6. 演示删除操作 (Delete)
    printf("把《Checklist》从歌单中删除。\n");

    targetNode = findByTitle(playlist, "Checklist");

     printf("这个操作的时间复杂度是O(1)，因为我们已经通过findByTitle函数找到了目标节点，不需要再去遍历链表了\n");

    if (targetNode) 
    {

        deleteNode(playlist, targetNode);

        printListForward(playlist);

    }
    else {

        printf("没有找到 《Checklist》 这首歌，无法进行删除操作！\n");
    }

    printf("\n");

    // 7. 演示删除头节点
    printf("把歌单的第一首歌《First Class》删除\n");

    printf("这个操作的时间复杂度是O(1)，因为我们有指向头节点的head指针，不需要遍历链表了\n");

    Node* headNode = playlist->head;

    if (headNode) {

        deleteNode(playlist, headNode);

        printListForward(playlist);

    }

    printf("\n");


    // 8. 演示删除尾节点
    printf("删除歌单的最后一首歌《Sinos De Natal\n");

    printf("这个操作的时间复杂度也是O(1)，因为我们有指向尾节点的tail指针，不需要遍历链表了\n");

    Node* tailNode = playlist->tail;

    if (tailNode) {

        deleteNode(playlist, tailNode);

        printListForward(playlist);

    }

    printf("\n");

    // 演示完毕，释放所有分配的内存
    freeList(playlist);

    printf("歌单已清空.\n");

    return EXIT_SUCCESS;
}