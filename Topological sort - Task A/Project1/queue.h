#ifndef __QUEUE__H
#define __QUEUE__H
#define SUCCESS 1
#define FAILURE 0

typedef struct Queue{
	int data;
	struct Queue *next;
} *qNode;

int initQueue(qNode *q, int data);
int enQueue(qNode *q, int data);
int deQueue(qNode *q);

#endif