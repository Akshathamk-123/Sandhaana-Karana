#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

queue_t* create_queue()   // return a newly created empty queue
{
	// DO NOT MODIFY!!!
	queue_t* Q = (queue_t*) malloc(sizeof(queue_t));
	Q->list = create_list();
	Q->front = Q->list->head;
	Q->rear = Q->list->tail;
	Q->size = Q->list->size;
	return Q;
}

void enqueue(queue_t* q, int data) // TODO: insert data at the end of a queue
{
	node_t *temp,*p;
    p=q->rear;
    temp=(node_t*)malloc(sizeof(node_t));
    temp->data=data;
    temp->next=NULL;
    if(p==NULL){
       q->front=temp->prev;
        p=temp->next;
    }
    else{
        p->next=temp;
        temp->prev=p;
    }
    q->rear=temp;
   
}

int dequeue(queue_t* q) 	// TODO: return the data at the front of a queue and remove it. Return -1 if queue is empty
{
	node_t *p;
    p=q->front;
    if(empty(q))  
    {
        return -1;
    }
    q->front=p->next;
    return p->data;
    free(p); 
}

int front(queue_t* q) // TODO: return the data at the front of a queue. Return -1 if queue is empty
{
    node_t *p;
    p=q->front;
    if(empty(q))  
    {   
        return -1;
    }
    q->front=p->next;
    return p->data;
}

int empty(queue_t* q) // return if the queue is empty
{
	// DO NOT MODIFY!!!
	return is_empty(q->list);
}

int queue_size(queue_t* q) // returns the number of elements in the queue
{
	// DO NOT MODIFY!!!
	return q->size;
}

void delete_queue(queue_t* q) // empty the contents of the queue
{
	// DO NOT MODIFY!!!
	delete_list(q->list);
	free(q);
}

void display(queue_t* q){
    node_t *p;
    p=q->list->head;
    if(p==NULL) printf("Empty queue\n");
    else{
        while(p!=NULL)
        {
            printf("%d\t",p->data);
            p=p->next;
        }
    }
}