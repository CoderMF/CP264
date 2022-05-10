/**
 * -------------------------
 * Student Name: Maham Farooq
 * Student ID: 200498180
 * Student email: faro8180@mylaurier.ca
 * -------------------------
 */

# include <stdio.h>
# include <stdlib.h>
# include <assert.h>
# include "heap.h"

void heapify_up(Heap *h, int i);
void heapify_down(Heap *h, int i);

Heap* create_heap(int capacity) {
	Heap *h = (Heap*) malloc(sizeof(Heap));
	if (capacity <= 0) {
		printf("Error(create_heap): invalid capcacity, capacity set to 1\n");
		h->capacity = 1;
	} else
		h->capacity = capacity;
	h->size = 0;
	h->array = (Data*) malloc(sizeof(Data) * h->capacity);
	return h;
}

void destroy_heap(Heap **h) {
	assert(h && *h);
	while (!is_empty_heap(*h))
		remove_heap(*h);
	free((*h)->array);
	(*h)->array = NULL;
	(*h)->capacity = 0;
	(*h)->size = 0;
	free(*h);
	*h = NULL;
	return;
}

int is_empty_heap(Heap *h) {
	assert(h);
	return (h->size == 0);
}

void insert_heap(Heap *h, Data *d) {
	assert(h && d);
	if (contains_heap(h, d)) {
		printf("Error(insert_heap): cannot insert a duplicate\n");
		return;
	}
	// if heap is full --> expand memory (double the size)
	if (h->capacity == h->size) {
		h->capacity = h->capacity * 2;
		h->array = realloc(h->array, sizeof(Data) * h->capacity);
	}

	h->array[h->size] = *copy_data(d);
	h->size++;
	heapify_up(h, h->size - 1);	// private func -> second parameter is index of last item inserted
	return;
}

void heapify_up(Heap *h, int i) {
	assert(h);
	// base case
	if (i <= 0)
		return;

	if (compare_data(&h->array[i], &h->array[Parent(i)]) == 1) {
		swap_data(&h->array[i], &h->array[Parent(i)]);
		heapify_up(h, Parent(i));
	}
//	heapify_up(h, Parent(i));	// recursion
	return;
}

Data* peek_heap(Heap *h) {
	assert(h);
	if (is_empty_heap(h)) {
		printf("Error(peek_heap): heap is empty\n");
		return NULL;
	}
	return copy_data(&h->array[0]);
}

void remove_heap(Heap *h) {
	assert(h);
	if (is_empty_heap(h)) {
		printf("Error(remove_heap): Cannot delete from an empty heap\n");
		return;
	}

	// if less than 1/3 heap utilized --> shrink capacity (half capacity)
	// 1/3 based on imperical data
	if (h->size < (h->capacity / 3)) {
		h->capacity = h->capacity / 2;
		h->array = realloc(h->array, (sizeof(Data) * h->capacity));
	}

	h->array[0] = *copy_data(&h->array[h->size - 1]);
	h->size--;
	heapify_down(h, 0);
	return;
}

void heapify_down(Heap *h, int i) {
	assert(h);
	// base case: if heap has single item or empty --> no need to heapify
	if (h->size <= 1)
		return;

	Data *node = &h->array[i];
	Data *left = NULL, *right = NULL;
	if (Left(i) < h->size)
		left = &h->array[Left(i)];
	if (Right(i) < h->size)
		right = &h->array[Right(i)];

	//// Base Case: if node has no children --> stop
	if (!left && !right)
		return;

	//// only single child
	if (!right) {	// only left child
		if (compare_data(left, node) == 1) {
			swap_data(left, node);
			heapify_down(h, Left(i));
			return;
		} else
			// Base case: one single left child smaller than node
			return;
		// Note: not possible to have only right child
	}

	//// 2 children cases
	// Case 1: left is largest
	if (compare_data(left, node) == 1 && compare_data(left, right) == 1) {
		swap_data(node, left);
		heapify_down(h, Left(i));
		return;
	}
	// Case 2: right is largest
	if (compare_data(right, node) == 1 && compare_data(right, left) == 1) {
		swap_data(node, right);
		heapify_down(h, Right(i));
		return;
	}
	// Case 3: node is largest
	return;// base case since node is right position in heap
}

int contains_heap(Heap *h, Data *d) {
	assert(h && d);
	if (is_empty_heap(h))
		return False;
	for (int i = 0; i < h->size; i++)
		if (compare_data(d, &h->array[i]) == 0)
			return True;
	return False;
}

void print_heap(Heap *h) {
	assert(h);
	printf("heap Capacity = %d, size = %d\n", h->capacity, h->size);
	if (is_empty_heap(h)) {
		printf("<empty heap>\n");
		return;
	}
	int i;
	printf("[");
	for (i = 0; i < h->size - 1; i++) {
		print_data(&h->array[i]);
		printf(" , ");
	}
	printf("%d]\n", h->array[h->size - 1]);
	return;
}

/*
 * -----------------------------------------------------
 * Algorithm name: Bubble Sort
 *
 * Time Complexity:
 * 				Comparisons		Swaps
 * Worst Case: 		O(log n)		O(log n)
 * Best Case: 		O(1)			O(1)
 * Average Case:	O(log n)		O(log n)
 *
 * Memory: O(n)
 *
 *-----------------------------------------------------
 */
void heap_sort(Data *array, const int size) {
	assert(array);
	Heap *h = create_heap(size);
	for (int i = 0; i < size; i++)
		insert_heap(h, &array[i]);
	for (int i = 0; i < size; i++) {
		array[i] = *peek_heap(h);
		remove_heap(h);
	}
	destroy_heap(&h);
	return;
}

int get_leaves(Heap *h, int *leaves_array) {
	int counter = 0, i = 0;
	for (i = 0; i < h->size; i++) {
		if (Left(i) >= h->size && Right(i) >= h->size) {
			counter++;
			leaves_array[counter - 1] = i;
		}
	}
	return counter;
}

Data* find_max_heap(Heap *h) {
	assert(h);
	if (is_empty_heap(h)) {
		printf("Error(find_max_heap): empty heap\n");
		return NULL;
	}
	return copy_data(&h->array[0]);
}

Data* find_min_heap(Heap *h) {
	assert(h);
	if (is_empty_heap(h)) {
		printf("Error(find_min_heap): empty heap\n");
		return NULL;
	}
	Data *min = copy_data(&h->array[0]);
	int i = 0;
	for (i = 0; i < h->size; i++) {
		if (*min > h->array[i]) {
			min = copy_data(&h->array[i]);
		}
	}
	return copy_data(min);
}

void heap_sort2(Data *array, const int size) {
	assert(array);

	Heap *h = create_heap(size);
	for (int i = 0; i < size; i++)
		insert_heap(h, &array[i]);
	for (int i = 0; i < size; i++) {
		array[i] = *peek_heap(h);
		remove_heap(h);
	}
	Data *array2 = (int*) malloc(sizeof(int) * size);
	for (int i = 0; i < size; i++) {
		array2[i] = array[size - i - 1];
	}
	for (int i = 0; i < size; i++) {
		array[i] = array2[i];
	}
	free(array2);
	destroy_heap(&h);
	return;
}
