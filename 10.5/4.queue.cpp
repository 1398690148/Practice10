/*************************************************************************
	> File Name: 4.queue.cpp
	> Author: 
	> Mail: 
	> Created Time: 2019年10月05日 星期六 15时52分41秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Queue {
    int *data;
    int head, tail, length, count;
} Queue;

Queue *init(int n) {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->data = (int *)malloc(sizeof(int) * n);
    q->head = q->tail = q->count = 0;
    q->length = n;
    return q;
}

void expand(Queue *q) {
    int *old_data = q->data;
    q->length *= 2;
    q->data = (int *)malloc(sizeof(int) * q->length);
    for (int i = q->head, j = 0; j < q->count; j++) {
        q->data[j] = old_data[(i + j) % (q->length / 2)];
    }
    q->tail = q->count;
    return ;
}

int push(Queue *q, int val) {
    if (q == NULL) return 0;
    if (q->count == q->length) {
        expand(q);
        printf("expand success!\n");
    }
    q->data[q->tail] = val;
    q->tail += 1;
    if (q->tail == q->length) {
        q->tail -= q->length;
    }
    q->count += 1;
    return 1;
}

int empty(Queue *q) {
    return q->count == 0;
}

int pop(Queue *q) {
    if (q == NULL) return 0;
    if (empty(q)) return 0;
    q->head += 1;
    if (q->head == q->length) q->head -= q->length;
    q->count -= 1;
    return 1;
}

int front(Queue *q) {
    if (q == NULL) return 0;
    return q->data[q->head];
}

void clear(Queue *q) {
    if (q == NULL) return ;
    free(q->data);
    free(q);
    return ;
}

void output(Queue *q) {
    printf("Queue(%d) =[", q->count);
    for (int i = q->head, j = 0; j < q->count; j++) {
        j && printf(", ");
        printf("%d", q->data[(i + j) % q->length]);
    }
    printf("]\n");
    return ;
}

int main() {
    srand(time(0));
    #define max_op 20
    Queue *queue = init(2);
    int op, val;
    for (int i = 0; i < max_op; i++) {
        op = rand() % 4;
        val = rand() % 100;
        switch (op) {
            case 0:
            case 1:
            case 2: {
                printf("push %d to Queue = %d\n", val, push(queue, val));
                output(queue);
                printf("\n");
            } break;
            case 3: {
                printf("pop %d", front(queue));
                printf(" from the Queue = %d\n", pop(queue));
                output(queue);
                printf("\n");
            } break;
        }
    }
    clear(queue);
    return 0;
}

