#include "queue.h"
#include <stdlib.h>

int initQueue(qNode *q, int data){
	*q = (qNode)malloc(sizeof(struct Queue));
	(*q)->data = data;
	(*q)->next = NULL;
	return 1;
}

int enQueue(qNode *q, int data){
	//if first node in this queue is null then create first node
	if (! *q){
		*q = (qNode)malloc(sizeof(struct Queue));
		(*q)->data = data;
		(*q)->next = NULL;
	} else{
		//create a new node for queue and insert into end of queue
		qNode newNode = (qNode)malloc(sizeof(struct Queue));
		(newNode)->data = data;
		(newNode)->next = NULL;

		qNode temp = *q; //temp is used to traverse this queue
		while (temp->next != NULL){
			temp = temp->next; 
		}

		temp->next = newNode;
	}

	return SUCCESS;
}

int deQueue(qNode *q){
	qNode temp = *q;
	*q = (*q)->next;
	int data = temp->data;
	free(temp);
	return data;
}