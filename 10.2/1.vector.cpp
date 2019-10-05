/*************************************************************************
	> File Name: 1.vector.cpp
	> Author: 
	> Mail: 
	> Created Time: 2019年10月02日 星期三 15时14分47秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Vector {
    int size, length;
    int *data;
}Vector;

Vector *init(int size) {
    Vector *vector = (Vector *)malloc(sizeof(Vector));
    vector->data = (int *)malloc(sizeof(int) * size);
    vector->size = size;
    vector->length = 0;
    return vector;
}

int expand(Vector *vector) {
    int extra_size = vector->size;
    int *p;
    while (extra_size) {
        p = (int *)realloc(vector->data, sizeof(int) * (vector->size + extra_size));
        if (p) break;
        extra_size /= 2;
    }
    if (p == NULL) return 0;
    vector->size += extra_size;
    vector->data = p;
    return 1;
}

int insert(Vector *vector, int ind, int value) {
    if (vector == NULL) return 0;
    if (ind < 0 || ind > vector->length) return 0;
    if (vector->length >= vector->size) {
        if (!expand(vector)) return 0;
        printf("expand Vector success = (%d)\n", vector->size);
    }
    for (int i = vector->length; i > ind; i--) {
        vector->data[i] = vector->data[i - 1];
    }
    vector->data[ind] = value;
    vector->length++;
    return 1;
}

int erase(Vector *vector, int ind) {
    if (vector == NULL) return 0;
    if (ind < 0 || ind >= vector->length) return 0;
    for (int i = ind + 1; i < vector->length; i++) {
        vector->data[i - 1] = vector->data[i];
    }
    vector->length--;
    return 1;
}

void output(Vector *vector) {
    printf("Vector(%d) = [", vector->length);
    for (int i = 0; i < vector->length; i++) {
        i && printf(", ");
        printf("%d", vector->data[i]);
    }
    printf("]\n");
    return ;
}

void clear(Vector *vector) {
    if (vector == NULL) return ;
    free(vector->data);
    free(vector);
}

int main() {
    srand(time(0));
    Vector *vector = init(1);
    #define max_op 20
    int op, ind, val;
    for (int i = 0; i < max_op; i++) {
        op = rand() % 4;
        ind = rand() % (vector->length + 3) - 1;
        val = rand() % 100;
        switch(op) {
            case 2:
            case 3:
            case 0: {
                printf("insert %d at %d to Vector = %d\n", 
                       val, ind, insert(vector, ind, val));
                output(vector);
                printf("\n");
            } break;
            case 1: {
                printf("erase element at %d from Vector = %d\n",
                      ind, erase(vector, ind));
                output(vector);
                printf("\n");
            } break;
        }
    }
    clear(vector);
    return 0;
}
