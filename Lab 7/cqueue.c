/*
 * ---------------------------------
 * Student Name: Maham Farooq
 * Student ID: 
 * Student Email: 
 * ---------------------------------
 */

# include <stdio.h>
# include <stdlib.h>
# include <assert.h>

# include "cqueue.h"

cQueue* create_cqueue(int capacity) {
	cQueue *q = (cQueue*) malloc(sizeof(cQueue));
	if (capacity < 1) {
		printf("Error(create_cqueue): invalid cqueue capacity, set to 10\n");
		capacity = 10;
	}
	q->capacity = capacity;
	q->array = (Data*) malloc(sizeof(Data) * capacity);
	q->front = -1;
	q->rear = -1;
	q->size = 0;
	return q;
}
int is_empty_cqueue(cQueue *q) {
	assert(q!=NULL);
	return (q->size == 0);
}

int len_cqueue(cQueue *q) {
	return q->size;
}

int is_full_cqueue(cQueue *q) {
	assert(q!=NULL);
	return (q->size == q->capacity);
}

int insert_cqueue(cQueue *q, Data *d) {
	assert(q!=NULL && d!=NULL);
	if (is_full_cqueue(q)) {
		printf("Error(insert_cqueue): cqueue is full\n");
		return False;
	}
	if (is_empty_cqueue(q))
		q->front++;

	//how to update rear-example: [_,_,1,2,3]	capacity = 5, front = 2, rear = (4+1)%capacity
	// to get to element 0 in circular array
	q->rear = (q->rear + 1) % q->capacity;
	q->array[q->rear] = *copy_data(d); // array of data objects not pointers (*copy_data(d))
	q->size++;
	return True;

}

Data* peek_cqueue(cQueue *q) {
	assert(q!=NULL);
	if (is_empty_cqueue(q)) {
		printf("Error(peek_cqueue): cQueue is empty\n");
		return NULL;
	}
	return copy_data(&q->array[q->front]);
}

Data* remove_cqueue(cQueue *q) {
	assert(q!=NULL);
	Data *d = NULL;
	if (is_empty_cqueue(q)) {
		printf("Error(remove_queue): Queue is empty\n");
		return d;
	}
	d = copy_data(&q->array[q->front]);	// want to destroy data in array
	Data *temp = &q->array[q->front];
	destroy_data(&temp);
	// when removing an item, front get incremented
	q->front = (q->front + 1) % q->capacity;
	q->size--;
	if (len_cqueue(q) == 0) {
		q->front = -1;
		q->rear = -1;
	}
	return d;
// remove done in lab
// change front--> [4,_,1,2,3]		capacity = 5, front = 2, rear = 0
// if removing, must change front value
// front also has to be able to set back to element 0 (so loops)
}

void destroy_cqueue(cQueue **q) {
	assert(q!=NULL);
	Data *d = NULL;
	while (!is_empty_cqueue(*q)) {
		d = remove_cqueue(*q);	// define pointer then destroy pointer
		destroy_data(&d);
	}
	free((*q)->array);
	(*q)->array = NULL;
	(*q)->capacity = 0;
	(*q)->front = 0;
	(*q)->rear = 0;
	(*q)->size = 0;

	free(*q);
	*q = NULL;
	return;
}
void print_cqueue(cQueue *q) {
// print done in lab
// be able to loop from front to rear and take care of circular matter
	assert(q != NULL);
	printf("Capacity = %d, Size = %d, front = %d, rear = %d\n", q->capacity,
			len_cqueue(q), q->front, q->rear);
	if (is_empty_cqueue(q)) {
		printf("<empty_cqueue>\n");
	} else {	// showing every 5 items/line
		int counter = 0, i = 0;
		for (i = q->front; i < (q->front + q->size); i++) {
			print_data(&q->array[i % q->capacity]);

			if ((counter + 1) % 5 == 0 && counter != len_cqueue(q) - 1) {
				printf("\n");
			} else
				printf("\t");
			counter++;
		}
		printf("\n");

	}
	return;
//	assert(q != NULL);
//	printf("Capacity = %d, Size = %d, front = %d, rear = %d\n", q->capacity,
//			len_cqueue(q), q->front, q->rear);
//	if (is_empty_cqueue(q)) {
//		printf("<empty_queue>\n");
//	} else {	// showing every 5 items/line
//		int counter = 0, i = 0;
//		int front = q->front;
//		int rear = q->rear;
//		if (front <= rear) {
//			while (front <= rear) {
//				print_data(&q->array[i]);
//				if ((counter + 1) % 5 == 0 && counter != len_cqueue(q) - 1) {
//					printf("\n");
//				} else
//					printf("\t");
//				counter++;
//				front++;
//				i++;
//			}
//		} else {
//			while (front <= len_cqueue(q) - 1) {
//				print_data(&q->array[i]);
//				if ((counter + 1) % 5 == 0 && counter != len_cqueue(q) - 1) {
//					printf("\n");
//				} else
//					printf("\t");
//				counter++;
//				front++;
//				i++;
//			}
//
//		}

//		for (i = q->front; i <= q->rear; i++) {
//			print_data(&q->array[i]);
//			if ((counter + 1) % 5 == 0 && counter != len_cqueue(q) - 1) {
//				printf("\n");
//			} else
//				printf("\t");
//			counter++;
//		}
//		printf("\n");
//	}
//	return;

}

int get_capacity_cqueue(cQueue *q) {
	return q->capacity;
}
