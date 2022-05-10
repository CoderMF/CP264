/*
 * ---------------------------------
 * Student Name: Maham Farooq
 * Student ID:	
 * Student Email: 
 * ---------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "A6.h"
#include "stack_array.h"

int is_equal_data(Data *d1, Data *d2) {
	return is_equal_process(d1, d2);
}

void remove_shortest(Process *processes, const int size) {
	if (processes == NULL) {
		printf("Error(remove_shortest): given pointer is NULL\n");
		return;
	}
	if (size <= 0) {
		printf("Error(remove_shortest): invalid array size\n");
		return;
	}
	int shorterA = processes[0].arrival;
	int shorterT = processes[0].time;
	long shorterP = processes[0].PID;
	int counter = 0, i = 0;

	if (size == 1) {
		printf("Shortest Process is : %ld\n", shorterP);
		processes[0].arrival = 0;
		processes[0].time = 0;
		processes[0].PID = 0;
		return;
	}

	for (int i = 0; i < size; ++i) {
		if (processes[i].time < shorterT) {
			shorterA = processes[i].arrival;
			shorterP = processes[i].PID;
			shorterT = processes[i].time;

		} else if (processes[i].time == shorterT) {
			if (processes[i].arrival < shorterA) {
				shorterA = processes[i].arrival;
				shorterP = processes[i].PID;
				shorterT = processes[i].time;
			} else if (processes[i].arrival == shorterA) {
				if (processes[i].PID < shorterP) {
					shorterA = processes[i].arrival;
					shorterP = processes[i].PID;
					shorterT = processes[i].time;
				}

			}

		}
	}
	printf("Shortest Process is : %ld\n", shorterP);

	for (i = 0; i < size; i++) {
		if (processes[i].PID == shorterP) {
			processes[i] = processes[size - 1];
			break;
		}
		counter++;
	}
	processes = (Process*) realloc(processes, sizeof(Process) * (size - 1));

	return;
}
void reverse_stack(Stack *s) {
//	assert(s!=NULL);
	Stack *temp = copy_stack(s);

//	for (int i = 0; i < len; i++) {
	while (!is_empty_stack(s)) {
		pop_stack(s);
	}

//	for (int i = 0; i < len; i++) {
	while (!is_empty_stack(temp)) {
		push_stack(s, peek_stack(temp));
		pop_stack(temp);
	}

	return;
}

int contains_stack(Stack *s, Data *value) {
//	assert(s != NULL);
	if (value == NULL) {
		printf("Error(contains_stack): invalid data");
		return -1;
	}
	if (s == NULL) {
		printf("Error(contains_stack): invalid stack\n");
		return -1;
	}
	int bool = False;
//	Stack *test = copy_stack(s);
	Stack *check = create_stack(len_stack(s));
	while (!is_empty_stack(s)) {
		if (is_equal_data(peek_stack(s), value) == True) {
			bool = True;
			break;
		}
		push_stack(check, pop_stack(s));
//		printf("test 113\n");
	}

//	printf("Check: ");
//	print_stack(check);
//	printf("CAP CHECK: %d\n", check->capacity);
//	printf("CAP S: %d\n", s->capacity);

	while (!is_empty_stack(check)) {
//		printf("check 122\n");
		push_stack(s, pop_stack(check));
//		printf("check 120\n");
	}
//	printf("Stack: ");
//	print_stack(s);
//	printf("hellp");
	destroy_stack(&check);
	check = NULL;
	return bool;
}

int resize_stack(Stack *s, int new_capacity) {
//	int *n;
	if (new_capacity <= 0) {
		printf("Error(resize_stack): invalid capacity size.\n");
		return False;
	} else if (new_capacity == s->capacity) {
		return False;
	} else if (new_capacity > s->capacity) {
		s->capacity = new_capacity;
		return True;
	} else if (new_capacity < s->capacity) {
		s->capacity = new_capacity;
		if (!(len_stack(s) < new_capacity)) {
			for (int i = 0; i < new_capacity; i++) {
				pop_stack(s);
//				destroy_data(&n);
			}

			s->array = (Data*) realloc(s->array, sizeof(Data) * (new_capacity));

			return True;
		}

	}
	return False;
}

Stack* concat_stack(Stack *s1, Stack *s2) {

//	printf("helo157");
//	Stack *s1_temp = NULL;
//	Stack *s2_temp = NULL;
//	Stack *temp = create_stack((len_stack(s1) + len_stack(s2)));
//	Stack *final = create_stack((len_stack(s1) + len_stack(s2)));
	Stack *temp = create_stack((s1->capacity + s2->capacity));
	Stack *final = create_stack(s1->capacity + s2->capacity);

	temp->capacity = s1->capacity + s2->capacity;
	final->capacity = s1->capacity + s2->capacity;
	Stack *s1_temp = create_stack(s1->capacity);
	s1_temp->capacity = s1->capacity;
	Stack *s2_temp = create_stack(s2->capacity);
	s2_temp->capacity = s2->capacity;
	while (!(is_empty_stack(s2))) {
		Data *temp_data = peek_stack(s2);
		push_stack(temp, temp_data);
		push_stack(s2_temp, temp_data);
		pop_stack(s2);

//		destroy_data(*data);
	}
	while (!is_empty_stack(s1)) {
		push_stack(temp, peek_stack(s1));
		push_stack(s1_temp, peek_stack(s1));
		pop_stack(s1);
		//		destroy_data(*data);
	}
//	}

//	print_stack(temp);
	while (!is_empty_stack(temp)) {
		push_stack(final, pop_stack(temp));
	}
	while (!is_empty_stack(s1_temp)) {
		push_stack(s1, pop_stack(s1_temp));
	}
	while (!is_empty_stack(s2_temp)) {
		push_stack(s2, pop_stack(s2_temp));
	}

	destroy_stack(&s1_temp);
	destroy_stack(&s2_temp);
	destroy_stack(&temp);
	temp = NULL;
	s1_temp = NULL;
	s2_temp = NULL;

	return final;

}
