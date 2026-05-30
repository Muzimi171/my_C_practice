#define _CRT_SECURE_NO_WARNINGS 
#include "doubly_linked.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 静态内部函数，根据SongData创建一个对应的节点，
// 静态内存函数，不会直接调用，而是在其他函数里被调用，
// 并且只能在本文件里使用
static Node* _createNode(Data songData)
{
    Node* newNode = (Node*)malloc(sizeof(Node));

    if (newNode == NULL)
    {
        perror("节点动态内存申请失败！\n");
        return NULL;
    }

    newNode->song = (Data*)malloc(sizeof(Data));

    if (newNode->song == NULL)
    {
        perror("节点中song动态内存申请失败！\n");
        free(newNode);
        return NULL;
    }

    // 字符串末尾需要加上'\0'，而strlen函数返回的长度是字符串的可见字符数，是不包含'\0'的，所以我们在申请内存的时候需要加上1来存储这个'\0'
    
    // 否则就会导致字符串没有正确地以'\0'结尾了，这样在后续使用字符串的时候就会出现不可预测的行为，比如可能会访问到其他内存，所以我们必须要加上1来存储这个'\0'
    newNode->song->artist = (char*)malloc(strlen(songData.artist) + 1);


    newNode->song->title = (char*)malloc(strlen(songData.title) + 1);

    if (!newNode->song->title || !newNode->song->artist)
    {
        perror("节点中song的title或artist动态内存申请失败！\n");
        free(newNode->song->title);
        free(newNode->song->artist);
        free(newNode->song);
        free(newNode);
        return NULL;
    }

    /* 注意前面只是分配了内存，还没有把数据复制进去，所以这里要用strcpy把数据复制到分配的内存里
    
    之所以不直接赋值，是因为 song->artist 和 songData->artist 都是char指针，这两个指针现在都指向各自申请的动态内存，如果你直接赋值的话，会导致song->artist 和 songData->artist 指向的内存被覆盖，即上面分配的动态内存丢失了，也就是所谓的内存泄漏
    
    并且直接赋值的话，相当于是复制地址，而不是复制内容了，这时候如果重复使用这个函数创建多个相同歌曲信息的节点的话，不同节点之间的song->artist和song->title就会指向同一块内存了，这样就会导致数据混乱了，所以我们必须要用strcpy把数据复制到我们自己分配的动态内存里，这样每个节点的song->artist和song->title才会指向不同的内存了，数据也就不会混乱了

    并且说到底，songData.artist和songData.title是局部变量，函数执行完就会被销毁了，所以如果直接赋值的话，song->artist和song->title就会指向已经被销毁的内存，变成悬空指针了，所以我们必须要用strcpy把数据复制到我们自己分配的动态内存里，这样就不会有悬空指针了 */
    strcpy(newNode->song->artist, songData.artist);
    strcpy(newNode->song->title, songData.title);
    newNode->song->duration = songData.duration;

    newNode->prev = NULL;
    newNode->next = NULL;

    return newNode;
}

DoublyLinkedList* createList()
{
    DoublyLinkedList* list = (DoublyLinkedList*)malloc(sizeof(DoublyLinkedList));

    if (list == NULL)
    {
        perror("申请链表管理器list内存失败！\n");
        return NULL;
    }

    list->head = NULL;
    list->tail = NULL;

    list->size = 0;

    return list;
}

// 因为list是链表管理器，我们可以直接用list->head获得头结点head本身，
// 所以这里就不需要使用多重指针了
void freeList(DoublyLinkedList* list)
{
    if (list == NULL)
    {
        printf("链表管理器list是NULL，无法进行释放操作！\n");
        return;
    }

    Node* current = list->head;
    Node* nextCurrent = NULL;

    for (size_t i = 0; i < list->size; i++)
    {
        nextCurrent = current->next;

        free(current->song->artist);
        free(current->song->title);
        free(current->song);
        free(current);

        current = nextCurrent;
    }

    free(list);

    list = NULL;
}

bool append(DoublyLinkedList* list, Data songData)
{
    if (list == NULL)
    {
        printf("链表管理器list是NULL，无法进行append操作！\n");
        return false;
    }

    Node* newNode = _createNode(songData);

    if (newNode == NULL)
    {
        printf("节点内存申请失败，无法进行append操作\n");
        return false;
    }

    if (list->head == NULL)
    {
        list->head = newNode;
        list->tail = newNode;

        list->size++;

        return true;; 
    }

    list->tail->next = newNode;

    newNode->prev = list->tail;

    list->tail = newNode;

    list->size++;

    return true;
}

bool prepend(DoublyLinkedList* list, Data songData)
{
    if (list == NULL)
    {
        printf("链表管理器list是NULL，无法进行prepend操作！\n");
        return false;
    }

    Node* newNode = _createNode(songData);

    if (newNode == NULL)
    {
        printf("节点内存申请失败，无法进行prepend操作\n");
        return false;
    }

    if (list->head == NULL)
    {
        list->head = newNode;
        list->tail = newNode;
        list->size++;

        return true;
    }

    newNode->next = list->head;
    list->head->prev = newNode;

    list->head = newNode;

    list->size++;

    return true;
}

Node* findByTitle(const DoublyLinkedList* list, const char* title)
{
    if (list == NULL || title == NULL)
    {
        printf("链表管理器list或要查找的标题title是NULL，无法进行查找操作！\n");
        return NULL;
    }


    Node* current = list->head;

    while (current != NULL)
    {
        // 这里不可以直接用current->song->title == title来比较字符串，因为current->song->title和title都是指针，这样比较的结果是比较两个指针的地址是否相等了，而不是比较字符串的内容是否相等了
        
        //所以我们需要用strcmp函数来比较两个指针指向的内容是否相等，如果strcmp函数返回0，说明两个字符串的内容是相等的了
        if (strcmp(current->song->title, title) == 0)
        {
            return current;
        }

        current = current->next;
    }

    printf("链表中没有对应标题的节点！\n");
    return NULL;
}

bool insertAfter(DoublyLinkedList* list, Node* targetNode, Data songData)
{
    if (!list || !targetNode) {

		perror("链表管理器list或目标节点targetNode是NULL，无法进行插入操作！\n");

		return false; // 链表或目标节点为空

	}

    Node* newNode = _createNode(songData);

    if (newNode == NULL)
    {
        printf("创建插入节点失败，无法进行插入操作！\n");
        return false;
    }

    Node* toInsertNode = findByTitle(list, targetNode->song->title);

    if (toInsertNode == NULL)
    {
        printf("没有找到待插入节点，无法进行插入操作！\n");
        return false;
    }

    newNode->next = toInsertNode->next;
    newNode->prev = toInsertNode;

    // 如果目标节点的下一个节点不为NULL，那么就把目标节点的下一个节点的prev指针指向新节点了，如果目标节点的下一个节点为NULL了，说明目标节点是最后一个节点了，那么我们就需要更新链表管理器list的tail指针了，让它指向新节点了
    if (toInsertNode->next != NULL) 
    {
        toInsertNode->next->prev = newNode;
    } 
    else // 如果插入节点是最后一个节点，更新tail指针
    {
        list->tail = newNode; 
    }


    toInsertNode->next = newNode;

    list->size++;

    return true;
}

bool deleteNode(DoublyLinkedList* list, Node* targetNode)
{
    if (!list || !targetNode) 
    {
        perror("链表管理器list或目标节点targetNode是NULL，无法进行删除操作！\n");

        return false; // 链表或目标节点为空
    }

    Node* toDeleteNode = findByTitle(list, targetNode->song->title);

    if (toDeleteNode == NULL)
    {
        printf("没有找到待删除节点，无法进行删除操作！\n");
        return false;
    }

    Node* prevNode = toDeleteNode->prev;
    Node* nextNode = toDeleteNode->next;

    // 要删除的节点是头节点, 需要更新list->head指针，让它指向下一个节点了，如果要删除的节点不是头节点了，那么就需要把前一个节点的next指针指向下一个节点了
    if (prevNode == NULL)
    {
        list->head = nextNode;
    }
    else
    {
        prevNode->next = nextNode;
    }

    // 要删除的节点是尾节点, 需要更新list->tail指针，让它指向前一个节点了，如果要删除的节点不是尾节点了，那么就需要把下一个节点的prev指针指向前一个节点了
    if (nextNode == NULL)
    {
        list->tail = prevNode;
    }
    else
    {
        nextNode->prev = prevNode;
    }


    /* 觉得不好理解也可以用这样的方式来写：
    if (toDeleteNode->prev != NULL) {

		toDeleteNode->prev->next = toDeleteNode->next;

	}
	else {

		list->head = toDeleteNode->next;

	}

	if (toDeleteNode->next != NULL) {

		toDeleteNode->next->prev = toDeleteNode->prev;

	}
	else {

		list->tail = toDeleteNode->prev;

	}

    */


   free(toDeleteNode->song->artist);
   toDeleteNode->song->artist = NULL;

   free(toDeleteNode->song->title);
    toDeleteNode->song->title = NULL;

    free(toDeleteNode->song);
    toDeleteNode->song = NULL;

    // 注意，预防悬挂指针的操作要在释放节点之前完成，因为一旦释放了节点，toDeleteNode这个指针就会变成悬空指针了，如果在释放节点之后再去访问toDeleteNode->song->artist等内容的话，就相当于实在访问一个悬空指针，会导致不可预测的结果
    
    //所以我们要在释放toDeleteNode节点之前先把toDeleteNode->song->artist、toDeleteNode->song->title和toDeleteNode->song都置为NULL

   free(toDeleteNode);

   // 没必要给toDeleteNode置为NULL了，因为它是一个局部变量，函数执行完就会被销毁了，对链表不会有任何影响了
   list->size--;

   return true;
}

void printListForward(DoublyLinkedList* list)
{
    if (!list || !list->head)
    {
        printf("链表管理器list是NULL或者链表为空，无法进行正向打印操作！\n");
        return;
    }

    printf("目前歌单里的歌曲有 %d 首\n", list->size);

    Node* current = list->head;

    for (size_t i = 0; i < list->size; i++)
    {
        printf("No.%d : { Title: %s , Artist: %s , Duration: %d }\n", i + 1,current->song->title, current->song->artist, current->song->duration);

        current = current->next;
    }

    printf("歌单打印完毕！\n");
}

void printListBackward(DoublyLinkedList* list)
{
    if (!list || !list->tail)
    {
        printf("链表管理器list是NULL或者链表为空，无法进行反向打印操作！\n");
        return;
    }

    printf("目前歌单里的歌曲有 %d 首\n", list->size);

    Node* current = list->tail;

    for (size_t i = 0 ; i < list->size; i++)
    {
        printf("No.%d : { Title: %s, Artist: %s, Duration: %d }\n", i + 1, current->song->title, current->song->artist, current->song->duration);

        current = current->prev;
    }

    printf("歌单打印完毕！\n");
}