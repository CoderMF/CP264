/*
 * ---------------------------------
 * Student Name: Maham Farooq
 * Student ID: 200498180
 * Student Email: faro8180@mylaurier.ca
 * ---------------------------------
 */
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <assert.h>
# include "stack_array.h"

Stack* create_stack(int stack_capacity) {	// creates stack
	Stack *s = (Stack*) malloc(sizeof(Stack));
	if (stack_capacity < 1) {
		fprintf(stderr, "Error(create_stack): invalid capacity, set to 10\n");
		s->capacity = 10;
	}
	s->capacity = stack_capacity;
	s->array = (Data*) malloc(sizeof(Data) * (s->capacity));
	s->top = -1;	// -1 means you can't point to any language
	return s;
}
void destroy_stack(Stack **s) {
	assert(s != NULL);
	Data *data = NULL;
	while (!is_empty_stack(*s)) {
		data = pop_stack(*s);
		destroy_data(&data);
	}
	free((*s)->array);// pointer has highest precedence so must put it in b/w brackets
	(*s)->array = NULL;
	(*s)->capacity = 0;
	(*s)->top = 0;
	*s = NULL;
	return;
}
Data* pop_stack(Stack *s) {	// stack ADT (essential method)
	assert(s != NULL);
	Data *d = NULL;
	if (is_empty_stack(s)) {
		printf("Error(pop_stack): stack is empty\n");
		return d;
	}
	d = copy_data(&s->array[s->top]);	// accessing top of array
	// used &s since copy_data receives a pointer
	Data *temp = &s->array[s->top];
	destroy_data(&temp);	// destroy receives double pointer so need '&'
	s->top--;	// decrementing top
	return d;
}

int push_stack(Stack *s, Data *d) { 	//stack ADT (essential method)
	assert(s != NULL && d != NULL);
	if (is_full_stack(s)) {
		printf("Error(push_stack): stack is full\n");
		return False;
	}
	s->top++;
	s->array[s->top] = *copy_data(d);
	return True;

}

void print_stack(Stack *s) {	// need function for testing purposes
	assert(s != NULL);
	printf("Stack Size = %d\n", len_stack(s));
	if (is_empty_stack(s)) {
		printf("<empty_stack>\n");
	}
	for (int i = s->top; i >= 0; i--) {
		print_data(&s->array[i]);
		printf("\n");
	}
	return;
}

Data* peek_stack(Stack *s) {	// stack ADT (essential method)
	assert(s!=NULL);
	if (is_empty_stack(s)) {
		printf("Error(peek_stack): stack is empty\n");
		return NULL;
	}
	return copy_data(&(s->array[s->top]));
}

int len_stack(Stack *s) {
	// check length by checking value of top since it points to last value in stack
	assert(s!= NULL);
	return s->top + 1;//included +1 b/c if 1 item in stack, top would be at index 0 so have 1 item
}

int is_empty_stack(Stack *s) { // stack ADT (essential method)
	assert(s!= NULL);
	return (s->top == -1);	// top -1 indicates it's empty
}

int is_full_stack(Stack *s) {	// stack ADT (essential method)
	assert(s!= NULL);
	return (s->top == s->capacity - 1);
}

Stack* copy_stack(Stack *s) {	// rmr to deepcopy
	assert(s != NULL);
	Stack *s2 = create_stack(s->capacity);
	int i, size = len_stack(s);
	Data *array = (Data*) malloc(sizeof(Data) * size);
	for (i = 0; i < size; i++) {
		array[i] = *pop_stack(s);
	}
	for (i = size - 1; i >= 0; i--) {
		push_stack(s, &array[i]);
		push_stack(s2, &array[i]);
	}
	free(array);
	return s2;
}
