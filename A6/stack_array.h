/*
 -------------------------------------
 File:    stack_array.h
 Project: R7
 file description
 -------------------------------------
 Author:  your name here
 ID:      your ID here
 Email:   your Laurier email here
 Version  2021-06-21
 -------------------------------------
 */

#ifndef STACK_ARRAY_H_
#define STACK_ARRAY_H_

#define True 1
#define False 0

#include "data.h"

typedef struct {
	Data *array;	//stack array
	int top;// index for top of stack [1,2,3,4] top is element [-1] since analysis is O[1]
	int capacity;	// max capacity of stack
} Stack;

Stack* create_stack(int stack_capacity);	// creates stack
void destroy_stack(Stack **s);
Data* pop_stack(Stack *s);	// stack ADT (essential method)
int push_stack(Stack *s, Data *d); //stack ADT (essential method)
void print_stack(Stack *s);	// need function for testing purposes
Data* peek_stack(Stack *s);	// stack ADT (essential method)
int len_stack(Stack *s);
int is_empty_stack(Stack *s);	// stack ADT (essential method)
int is_full_stack(Stack *s);	// stack ADT (essential method)
Stack* copy_stack(Stack *s);

#endif /* STACK_ARRAY_H_ */
