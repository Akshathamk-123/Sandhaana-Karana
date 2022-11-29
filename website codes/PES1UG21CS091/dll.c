#include "dll.h"
#include <stdio.h>
#include <stdlib.h>
 
list_t* create_list()  // return a newly created empty doubly linked list
{
	// DO NOT MODIFY!!!
	list_t* l = (list_t*) malloc(sizeof(list_t));
	l->head = NULL;
	l->tail = NULL;
	l->size = 0;
	return l;
}

void insert_front(list_t* list, int data)  // TODO: inserts data to the beginning of the linked list
{
	node_t *newNode = (node_t *) malloc(sizeof(node_t));
	newNode->data = data;
	newNode->next = NULL;
	newNode->prev = NULL;
	if(is_empty(list))
	{
		list->head = list->tail = newNode;
	}
	else {
		newNode->next = list->head;
		list->head->prev = newNode;
		list->head = newNode;
	}
	list->size++;
}

void insert_back(list_t* list, int data) // TODO: inserts data to the end of the linked list
{
	node_t *newNode = (node_t *) malloc(sizeof(node_t));
	newNode->data = data;
	newNode->next = NULL;
	newNode->prev = NULL;
	if(is_empty(list))
	{
		list->head = list->tail = newNode;
	}
	else {
		newNode->prev = list->tail;
		list->tail->next = newNode;
		list->tail = newNode;
	}
	list->size++;
}

void insert_after(list_t* list, int data, int prev) // TODO: inserts data after the node with data “prev”. Do not insert or do anything if prev doesn't exist
{
	if(is_empty(list)) {
		// printf("List is Empty!\n");
		return;
	}
	else {
		node_t *temp = list->head;
		node_t *newNode = (node_t *) malloc(sizeof(node_t));
		newNode->data = data;
		newNode->next = NULL;
		newNode->prev = NULL;
		int found = 0;
		// Traversing list till prev is found in list
		while ((temp != NULL)&&(!found))
		{
			if(temp->data == prev)
			{
				found++;
				break;
			}
			temp = temp->next;
		}
		if(found) {
			if(temp == list->tail)
			{
				temp->next = newNode;
				newNode->prev = temp;
				list->tail = newNode;
			}
			else {
				newNode->next = temp->next;
				temp->next->prev = newNode;
				newNode->prev = temp;
				temp->next = newNode;
			}
			list->size++;
		}
	}
}

void delete_front(list_t* list) // TODO: delete the start node from the linked list.
{
	if(is_empty(list))
		return;

	node_t *temp = list->head;
	temp->next->prev = NULL;
	list->head = temp->next;
	list->size--;
	free(temp);
	temp = NULL;	
}

void delete_back(list_t* list) // TODO: delete the end node from the linked list.
{
	if(is_empty(list))
		return;

	node_t *temp = list->tail;
	temp->prev->next = NULL;
	list->tail = temp->prev;
	list->size--;
	free(temp);
	temp = NULL;
}

void delete_node(list_t* list, int data) // TODO: delete the node with “data” from the linked list.
{
	if(is_empty(list))
		return;

	node_t *temp = list->head;
	while((temp->data != data)&&(temp != NULL))
		temp = temp->next;

	if(temp->data == data) {
		if(temp == list->head)
			delete_front(list);
		else if (temp == list->tail)
			delete_back(list);
		else {
			temp->next->prev = temp->prev;
			temp->prev->next = temp->next;
			free(temp);
			temp = NULL;
			list->size--;
		}	
	}	
}

node_t* search(list_t* list, int data) // TODO: returns the pointer to the node with “data” field. Return NULL if not found.
{	
	if(is_empty(list))
		return NULL;

	node_t *cur = list->head;
	int found = 0;
	while((cur != NULL)&&(!found)) {
		if(cur->data == data) {
			found++;
		}
		else {
			cur = cur->next;
		}
	}	
	return cur;
}

int is_empty(list_t* list) // return true or 1 if the list is empty; else returns false or 0
{
	// DO NOT MODIFY!!!
	return list->size == 0;
}

int size(list_t* list) // returns the number of nodes in the linked list.  
{
	// DO NOT MODIFY!!!
	return list->size;
}

void delete_nodes(node_t* head) // helper
{
	// DO NOT MODIFY!!!
	if(head == NULL)
		return;
	delete_nodes(head->next);
	free(head);	
}

void delete_list(list_t* list) // free all the contents of the linked list
{
	// DO NOT MODIFY!!!
	delete_nodes(list->head);
	free(list);
}

void display_list(list_t* list) // print the linked list by separating each item by a space and a new line at the end of the linked list.
{
	// DO NOT MODIFY!!!
	node_t* it = list->head;
	while(it != NULL)
	{
		printf("%d ", it->data);
		it = it->next;
	}
	printf("\n");
}

