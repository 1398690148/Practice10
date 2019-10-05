/*************************************************************************
	> File Name: 2.list.cpp
	> Author: 
	> Mail: 
	> Created Time: 2019年10月02日 星期三 19时09分03秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct ListNode {
    int data;
    struct ListNode *next;
} ListNode;

typedef struct List {
    ListNode head;
    int length;
}List;

ListNode *init_ListNode(int val) {
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));
    p->data = val;
    p->next = NULL;
    return p;
}

List *init_List() {
    List *l = (List *)malloc(sizeof(List));
    l->head.next = NULL;
    l->length = 0;
    return l;
}

void clear_Node(ListNode *node) {
    if (node == NULL) return ;
    free(node);
    return ;
}

int insert(List *list, int ind, int val) {
    if (list == NULL) return 0;
    if (ind < 0 || ind > list->length) return 0;
    ListNode *p = &(list->head), *node = init_ListNode(val);
    while (ind--) p = p->next;
    node->next = p->next;
    p->next = node;
    list->length++;
    return 1;
}

int erase(List *list, int ind) {
    if (list == NULL) return 0;
    if (ind < 0 || ind >= list->length) return 0;
    ListNode *p = &(list->head), *q;
    while (ind--) p = p->next;
    q = p->next;
    p->next = q->next;
    clear_Node(q);
    list->length--;
    return 1;
}


void clear_List(List *list) {
    if (list == NULL) return;
    ListNode *p = list->head.next, *q;
    while (p != NULL) {
        q = p->next;
        clear_Node(p);
        p = q;
    }
    free(list);
    return ;
}

void output(List *l) {
    printf("list(%d) = [", l->length);
    for (ListNode *p = l->head.next; p; p = p->next) {
        printf("%d-> ", p->data);
    }
    printf("NULL ]\n");
}

int main() {
    srand(time(0));
    #define max_op 20
    int op, ind, val;
    List *l = init_List();
    for (int i = 0; i < max_op; i++) {
        op = rand() % 4;
        ind = rand() % (l->length + 3) - 1;
        val = rand() % 100;
        switch(op) {
            case 0:
            case 1:
            case 2: {
                printf("insert %d at %d to List = %d\n", 
                      val, ind, insert(l, ind, val));
                output(l);
                printf("\n");
            } break;
            case 3: {
               printf("erase item at %d from list = %d\n",
                     ind, erase(l, ind));
                output(l);
                printf("\n");
            } break;
        }
    }
    clear_List(l);
    return 0;
}
