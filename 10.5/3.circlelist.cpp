/*************************************************************************
	> File Name: 3.circlelist.cpp
	> Author: 
	> Mail: 
	> Created Time: 2019年10月05日 星期六 19时10分33秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *prior, *next;
} Node;

typedef struct LinkList {
    struct Node head;
    int length;
} LinkList;

LinkList *init_List() {
    LinkList *l = (LinkList *)malloc(sizeof(LinkList));
    l->head.prior = NULL;
    l->head.next = NULL;
    l->length = 0;
    return l;
}

Node *init_Node(int value) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = value;
    node->prior = NULL;
    node->next = NULL;
    return node;
}

int insert(LinkList *l, int ind, int val) {
    if (l == NULL) return 0;
    if (ind < 0 || ind > l->length) return 0;
    Node *p = &(l->head), *node = init_Node(val);
    while (ind--) p = p->next;
    node->next = p->next;
    if (p->next != NULL)
        p->next->prior = node;
    p->next = node;
    node->prior = p;
    l->length++;
    if (l->length == 1) {
        node->next = p->next;
        node->prior = p->next;
    }
    return 1;
}

void output(LinkList *l) {
    Node *p = l->head.next;
    for (int i = 0; i < l->length; ++i) {
        i && printf(" ");
        printf("%d", p->data);
        p = p->next;
    }
    return ;
}

void clear_Node(Node *node) {
    if (node == NULL) return ;
    free(node);
    return ;
}

void clear_List(LinkList *l) {
    if (l == NULL) return ;
    Node *p = l->head.next, *q;
    while (p) {
        q = p->next;
        clear_Node(p);
        p = q;
    }
    free(l);
    return ;
}

int main() {
    LinkList *l = init_List();
    for (int i = 0; i < 10; i++) {
        insert(l, i, i + 1);
    }
    output(l);
    printf("111");
    clear_List(l);
    return 0;
}
