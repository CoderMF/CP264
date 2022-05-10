#ifndef A6_H_
#define A6_H_

#include "stack_array.h"

#define MAX 100

void remove_shortest(Process *processes, const int size);
void reverse_stack(Stack *s);
int contains_stack(Stack *s, Data *value);
int resize_stack(Stack *s, int new_capacity);
Stack* concat_stack(Stack *s1, Stack *s2);

#endif /* A6_H_ */
