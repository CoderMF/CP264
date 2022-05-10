/*
 -------------------------------------
 File:    cqueue.h
 Project: R8
 file description
 -------------------------------------
 Author:  your name here
 ID:      your ID here
 Email:   your Laurier email here
 Version  2021-06-28
 -------------------------------------
 */

#ifndef CQUEUE_H_
#define CQUEUE_H_

#define True 1
#define False 0

#include "data.h"

typedef struct {
	Data *array;	// array containing data items
	int front;		// index of first item in Queue
	int rear;		// index of alst item in Queue
	int capacity;	// max queue length
	int size; 		// number of elements in Queue
} cQueue;

cQueue* create_cqueue(int capacity);
int is_empty_cqueue(cQueue *q);
int len_cqueue(cQueue *q);
int is_full_cqueue(cQueue *q);
int insert_cqueue(cQueue *q, Data *d);
void adjust_cqueue(cQueue *q);
Data* peek_cqueue(cQueue *q);
Data* remove_cqueue(cQueue *q);
void destroy_cqueue(cQueue **q);
void print_cqueue(cQueue *q);
int get_capacity_cqueue(cQueue *q);

#endif /* CQUEUE_H_ */
