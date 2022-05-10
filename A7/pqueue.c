/*
 * ---------------------------------
 * Student Name: Maham Farooq
 * Student ID: 200498180
 * Student Email: faro8180@mylaurier.ca
 * ---------------------------------
 */

# include <stdio.h>
# include <stdlib.h>
# include <assert.h>
# include "pqueue.h"

/**
 * ------------------------------------------------------------
 * Parameters: 	capacity: maximum size of priority queue
 * 				priority: a character describing priority mode
 * Returns: 	q: A pointer to a priority queue
 * Description:	Creates a priority queue
 * 				Dynamically creates an array of size: capacity
 * 				Sets front and rear to -1
 * 				priority is set to either 'H' or 'L'
 * 				if invalid capacity set to 10
 * 				if invalid priority set to 'H'
 * Assert:		None
 * Errors:		if invalid capacity:
 * 					Error(create_pqueue): invalid pqueue capacity, set to 10\n
 * 				if invalid priority:
 * 					"Error(create_pqueue): invalid priority, set to 'H'\n"
 * ------------------------------------------------------------
 */
pQueue* create_pqueue(int capacity, char priority) {
	pQueue *q = (pQueue*) malloc(sizeof(pQueue));
	if (capacity < 1) {
		printf("Error(create_pqueue): invalid pqueue capacity, set to 10\n");
		capacity = 10;
	}

	if (!(priority == 'H' || priority == 'L')) {
		printf("Error(create_pqueue): invalid priority, set to 'H'\n");
		priority = 'H';
	}

	q->capacity = capacity;
	q->array = (Data*) malloc(sizeof(Data) * capacity);
	q->front = -1;
	q->rear = -1;
	q->priority = priority;

	return q;
}

/**
 * ------------------------------------------------------------
 * Parameters: 	q: A pointer to a priority queue (pQueue*)
 * Returns: 	number of items in a pqueue (int)
 * Description:	Returns number of items in a pqueue
 * Assert:		q is not NULL
 * Errors:		None
 * ------------------------------------------------------------
 */
int len_pqueue(pQueue *q) {
	assert(q!=NULL);
	if (q->front == -1)
		return 0;

	return q->rear - q->front + 1;
}

/**
 * ------------------------------------------------------------
 * Parameters: 	q: A pointer to a priority queue (pQueue*)
 * Returns: 	pqueue capacity (int)
 * Description:	Returns maximum number of items that can be stored in a pqueue
 * Assert:		q is not NULL
 * Errors:		None
 * ------------------------------------------------------------
 */
int get_capacity_pqueue(pQueue *q) {
	assert(q!=NULL);
	return q->capacity;
}

/**
 * ------------------------------------------------------------
 * Parameters: 	q: A pointer to a priority queue (pQueue*)
 * Returns: 	True/False (int)
 * Description:	Returns True if pqueue is empty, False otherwise
 * Assert:		q is not NULL
 * Errors:		None
 * ------------------------------------------------------------
 */
int is_empty_pqueue(pQueue *q) {
	return len_pqueue(q) == 0;
}

/**
 * ------------------------------------------------------------
 * Parameters: 	q: A pointer to a priority queue (pQueue*)
 * Returns: 	True/False (int)
 * Description:	Returns True if pqueue is full, False otherwise
 * Assert:		q is not NULL
 * Errors:		None
 * ------------------------------------------------------------
 */
int is_full_pqueue(pQueue *q) {
	return len_pqueue(q) == q->capacity;
}

// prototype
int compare_data(Data *d1, Data *d2) {
	if (d1->time < d2->time)
		return 2;
	else if (d1->time > d2->time)
		return 1;
	else if (d1->time == d2->time) {
		if (d1->arrival < d2->arrival)
			return 2;
		else if (d1->arrival > d2->arrival)
			return 1;
		else if (d1->arrival == d2->arrival) {
			if (d1->PID < d2->PID)
				return 2;
			else if (d1->PID > d2->PID)
				return 1;
			else {
				return 0;
			}
		}
	}
	return 0;
}

/**
 * ------------------------------------------------------------
 * Parameters: q: A pointer to a priority Queue (pQueue*)
 * Returns: index: index of top priority item
 * Description: A private helper function mainly for unsorted
 * insertion pqueue
 * finds index of item with highest priority in pqueue
 * if 'H' --> finds largest value
 * if 'L' --> finds smallest value
 * Assert: q is not NULL
 * q is not empty
 * Errors: None
 * Analysis: O(n)
 * ------------------------------------------------------------
 */
int find_top_priority(pQueue *q) {
	assert(q!=NULL);
	assert(!is_empty_pqueue(q));
	int index = q->front;
	int i;
	for (i = q->front; i <= q->rear; i++) {
		if (q->priority == 'H'
				&& compare_data(&q->array[i], &q->array[index]) == 1)
			index = i;
		else if (q->priority == 'L'
				&& compare_data(&q->array[i], &q->array[index]) == 2)
			index = i;
	}
	return index;
}

void adjust_queue(pQueue *q) {
	assert(q!=NULL);
	int length = len_pqueue(q), i;
	for (i = 0; i < length; i++)
		q->array[i + q->front] = q->array[i];
	q->front = 0;
	q->rear = length + 1;
	return;
}

/**
 * ------------------------------------------------------------
 * Parameters: 	q: A pointer to a priority queue (pQueue*)
 * Returns: 	None
 * Description:	Prints contents of a priority queue
 * 				Starts with:
 * 					Capacity = <int>, Size = <int>, front = <int>, rear = <int>\n
 * 				Then prints queue elements separated by a tab
 * 				Each five elements appear on a separate line
 * 				if empty prints: <empty_pqueue>\n
 * Assert:		q is not NULL
 * Errors:		None
 * ------------------------------------------------------------
 */
void print_pqueue(pQueue *q) {
	assert(q != NULL);
	printf("Capacity = %d, Size = %d, front = %d, rear = %d\n", q->capacity,
			len_pqueue(q), q->front, q->rear);
	if (is_empty_pqueue(q)) {
		printf("<empty_pqueue>\n");
	} else {	// showing every 5 items/line
		int counter = 0, i;
		for (i = q->front; i <= q->rear; i++) {
			print_data(&q->array[i]);
			if ((counter + 1) % 5 == 0 && counter != len_pqueue(q) - 1) {
				printf("\n");
			} else
				printf("\t");
			counter++;
		}
		printf("\n");
	}
	return;
}

/**
 * ------------------------------------------------------------
 * Parameters: 	q: A pointer to a priority Queue (pQueue*)
 * 				d: A data item to be added (Data*)
 * Returns: 	True/False
 * Description:	Insert an item to the queue (unsorted insertion)
 * 				returns True if insert is successful and False otherwise
 * Assert:		q and d are not NULL
 * Errors:		if full --> Error(insert_pqueue): pqueue is full\n
 * Analysis: 	O(n) if regular queue
 * 				O(1) if circular queue
 * ------------------------------------------------------------
 */
int insert_pqueue(pQueue *q, Data *d) {
	assert(q!=NULL && d!=NULL);
	if (is_full_pqueue(q)) {
		printf("Error(insert_pqueue): pqueue is full\n");
		return False;
	}
	if (is_empty_pqueue(q)) {
		q->front = 0;
	}
	q->rear++;
	q->array[q->rear] = *copy_data(d); // array of data objects not pointers (*copy_data(d))
	return True;
}

/**
 * ------------------------------------------------------------
 * Parameters: 	q: A pointer to a priority Queue (pQueue*)
 * 				d: A data item to be added (Data*)
 * Returns: 	True/False
 * Description:	Insert an item to the queue (sorted insertion)
 * 				returns True if insert is successful and False otherwise
 * Assert:		q and d are not NULL
 * Errors:		if full --> Error(insert_pqueue): pqueue is full\n
 * Analysis: 	O(n)
 * ------------------------------------------------------------
 */
int insert_pqueue2(pQueue *q, Data *d) {
	assert(q!=NULL && d!=NULL);
	if (is_full_pqueue(q)) {
		printf("Error(insert_pqueue2): pqueue is full\n");
		return False;
	}
	if (is_empty_pqueue(q)) {
		q->front++;
	}
	if (q->rear == q->capacity - 1) {
		adjust_queue(q);
	}
	q->rear++;
	int index = q->front, i;

	for (i = q->front; i < q->rear; i++) {
		if (q->priority == 'H' && compare_data(d, &q->array[i]) == 2)
			index = i + 1;
		else if (q->priority == 'L' && compare_data(d, &q->array[i]) == 1)
			index = i + 1;
	}

	for (i = q->rear; i > index; i--)
		q->array[i] = q->array[i - 1];
	q->array[index] = *copy_data(d);

	return True;

}

/**
 * ------------------------------------------------------------
 * Parameters: 	q: A pointer to a priority Queue (pQueue*)
 * Returns: 	d: a copy of data item at the front of pqueue
 * Description:	Returns a copy of front of pqueue
 * 				Assumes unsorted insert
 * Assert:		q is not NULL
 * Errors:		if empty --> Error(peek_pqueue): pqueue is empty\n
 * Analysis: 	O(n)
 * ------------------------------------------------------------
 */
Data* peek_pqueue(pQueue *q) {
	assert(q!=NULL);

	if (is_empty_pqueue(q)) {
		printf("Error(peek_pqueue): pqueue is empty\n");
		return NULL;
	}
	int index = find_top_priority(q);

	Data *final = &q->array[index];

	return copy_data(final);

}

/**
 * ------------------------------------------------------------
 * Parameters: 	q: A pointer to a priority Queue (pQueue*)
 * Returns: 	d: a copy of data item at the front of pqueue
 * Description:	Returns a copy of front of pqueue
 * 				Assumes sorted insert
 * Assert:		q is not NULL
 * Errors:		if empty --> Error(peek_pqueue): pqueue is empty\n
 * Analysis: 	O(1)
 * ------------------------------------------------------------
 */
Data* peek_pqueue2(pQueue *q) {
	assert(q!=NULL);

	if (is_empty_pqueue(q)) {
		printf("Error(peek_pqueue2): pqueue is empty\n");
		return NULL;
	}
	return copy_data(&q->array[q->front]);
}

/**
 * ------------------------------------------------------------
 * Parameters: 	q: A pointer to a priority Queue (pQueue*)
 * Returns: 	d: a copy of data item at the front of pqueue
 * Description:	Returns a copy of front of pqueue
 * 				Assumes unsorted insert
 * Assert:		q is not NULL
 * Errors:		if empty --> Error(remove_pqueue): pqueue is empty\n
 * Analysis: 	O(n)
 * ------------------------------------------------------------
 */
Data* remove_pqueue(pQueue *q) {
	assert(q!=NULL);
	Data *d = NULL;
	if (is_empty_pqueue(q)) {
		printf("Error(remove_pqueue): Queue is empty\n");
		return d;
	}
	int ind = find_top_priority(q);
	d = copy_data(&q->array[ind]);	// want to destroy data in array
	int i = 0;

	Data *temp = (&q->array[ind]);
	destroy_data(&temp);

	if (ind == q->front) {
		q->front++;
//		q->front = 0;
	} else {
		for (i = ind; i < q->rear; i++) {
			q->array[i] = q->array[i + 1];
		}
		q->rear--;
	}
//	q->front = 0;
	if (len_pqueue(q) == 0) {
		q->front = -1;
		q->rear = -1;
	}
	return d;
}

/**
 * ------------------------------------------------------------
 * Parameters: 	q: A pointer to a priority Queue (pQueue*)
 * Returns: 	d: a copy of data item at the front of pqueue
 * Description:	Returns a copy of front of pqueue
 * 				Assumes sorted insert
 * Assert:		q is not NULL
 * Errors:		if empty --> Error(remove_pqueue2): pqueue is empty\n
 * Analysis: 	O(1)
 * ------------------------------------------------------------
 */
Data* remove_pqueue2(pQueue *q) {
	assert(q!=NULL);
	Data *d = NULL;
	if (is_empty_pqueue(q)) {
		printf("Error(remove_queue): pqueue is empty\n");
		return d;
	}
	d = copy_data(&q->array[q->front]);	// want to destroy data in array
	Data *temp = &q->array[q->front];
	destroy_data(&temp);
	// when removing an item, front get incremented
	q->front++;
	if (len_pqueue(q) == 0) {
		q->front = -1;
		q->rear = -1;
	}

	return d;
}

/**
 * ------------------------------------------------------------
 * Parameters: 	q: A double pointer to a priority Queue (pQueue**)
 * Returns: 	None
 * Description:	Destroy a queue by:
 * 					removing and destroying all data items
 * 					freeing queue array
 * 					set all other data members to 0
 * 					free queue
 * 				Assumes sorted insert
 * Assert:		q is not NULL
 * Errors:		None
 * ------------------------------------------------------------
 */
void destroy_pqueue(pQueue **q) {
	assert(q!=NULL);
	Data *d = NULL;
	while (!is_empty_pqueue(*q)) {
		d = remove_pqueue(*q);	// define pointer then destroy pointer
		destroy_data(&d);
	}
	free((*q)->array);
	(*q)->array = NULL;
	(*q)->capacity = 0;
	(*q)->front = 0;
	(*q)->rear = 0;
	free(*q);
	*q = NULL;
	return;
}
