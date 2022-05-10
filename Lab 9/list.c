/*
 * ---------------------------------
 * Student Name: Maham Farooq
 * Student ID:	200498180
 * Student Email: faro8180@mylaurier.ca
 * ---------------------------------
 */

# include <stdio.h>
# include <stdlib.h>
# include <assert.h>
# include <assert.h>
#include "list.h"

//---------------- Node Implementation ------------------------

Node* create_node(Data *d, Node *n) {
	assert(d);
	// would not assert node bc want to allow node to be NULL
	Node *node = (Node*) malloc(sizeof(Node));
	node->data = copy_data(d);
	node->next = n;	// didn't copy cuz we want to point to data
	// now both next and data point to same structure
	return node;
}

void print_node(Node *n) {
	assert(n);
	print_data(n->data);
	return;
}

Node* copy_node(Node *n) {
	assert(n);
	return create_node(n->data, n->next);	// will create node then return it
}

void destroy_node(Node **n) {
	assert(n && *n);
	destroy_data(&(*n)->data);	// cuz its double pointer
	(*n)->data = NULL;
	(*n)->next = NULL;
	free(*n);
	return;
}

//---------------- Linked List Implementation ------------------------

List* create_list() {
	List *list = (List*) malloc(sizeof(List));
	list->head = NULL;
	list->size = 0;
	return list;
}

int is_empty_list(List *list) {
	assert(list);
	return (list->head == NULL);// could have used size but not all linked list have size
}

void print_list(List *list) {
	assert(list);
	Node *current_node = list->head;	// just need address of head
	while (current_node != NULL) {
		print_node(current_node);
		printf("-->");
		current_node = current_node->next;
	}
	printf("NULL\n");
	return;
}

void append_list(List *list, Data *d) {
	assert(list && d);
	Node *new_node = create_node(d, NULL);
	if (is_empty_list(list))
		list->head = new_node;
	else {
		Node *current_node = list->head;
		while (current_node->next != NULL)
			current_node = current_node->next;
		current_node->next = new_node;
	}
	list->size++;
	return;
}

void insert_front_list(List *list, Data *d) {
	assert(list && d);
	Node *new_node = create_node(d, list->head);
	list->head = new_node;
	list->size++;
	return;
}

// there is a dependency of get_data_list to get_node_list
// good if have tested well (stable and safe)
// bad if there's a problem here then problem will be in get_node_list
Data* get_data_list(List *list, int index) {
	assert(list);
	return get_node_list(list, index)->data;// not copying data cuz already do it below
}

// returns a copy of node, not reference
Node* get_node_list(List *list, int index) {
	assert(list);
	if (index < 0 || index >= list->size) {
		printf("Error(get_node_list): index out of range\n");
		return NULL;
	}
	Node *current_node = list->head;
	int i = 0;
	while (i < index && current_node != NULL) {
		current_node = current_node->next;
		i++;
	}
	return copy_node(current_node);
}

void destroy_list(List **list) {
	while (!is_empty_list(*list)) {
		remove_rear_list(*list);
	}
	(*list)->head = NULL;
	(*list)->size = 0;
	free(*list);
	*list = NULL;
	return;
}

Data* remove_rear_list(List *list) {
	assert(list);
	if (is_empty_list(list)) {
		printf("Error(remove_rear_list): list is empty\n");
		return NULL;
	}

	Node *previous = NULL;
	Node *current = list->head;

	while (current->next != NULL) {
		previous = current;
		current = current->next;
	}
	Data *item = copy_data(current->data);
	if (list->size == 1)
		list->head = NULL;
	else
		previous->next = NULL;
	destroy_node(&current);
	list->size--;

	return item;
}

// (front) 5-->10-->7->6-->NULL
// NULL <--5<--10<--7<--6 (front)
void reverse_list(List *list) {
	assert(list);
	if (is_empty_list(list))
		return;	// do nothing
	Node *previous_node, *current_node, *next_node;

	// initialize pointers
	previous_node = NULL;
	current_node = list->head;
	next_node = current_node->next;

	while (current_node->next != NULL) {
		current_node->next = previous_node;	// reverses link
		// update pointers for next round
		previous_node = current_node;
		current_node = next_node;
		next_node = next_node->next;
	}
	current_node->next = previous_node;
	// change front from beginning to end
	list->head = current_node;
	return;
}

List* array_to_list(Data *array, const int size) {
	assert(array);
	List *list = NULL;
	if (size <= 0) {
		printf("Error(arrya_to_list): invalid array size\n");
		return list;
	}
	int i;
	list = create_list();
	for (i = 0; i < size; i++) {
		append_list(list, &array[i]);// using append cuz it will preserve order
	}
	return list;
}

/**
 * ---------------------------------------------------------------------
 * Parameters: a pointer to a linked list (List*)
 * Returns: Copy of data stored in first node (Data*)
 * Description: returns copy of data stored in first node
 * if list is empty, prints error msg and returns NULL
 * Asserts: asserts given linked list is not Null
 * ---------------------------------------------------------------------
 */
Data* peek_list(List *list) {
	assert(list);
	if (list->size == 0) {
		printf("Error(peek_list): list is empty\n");
		return NULL;
	}
	Data *d = NULL;
	d = copy_data(list->head->data);
	return d;
}

/**
 * ---------------------------------------------------------------------
 * Parameters: a pointer to a linked list (List*)
 * Returns: None
 * Description: removes first item from linked list
 * if list is empty, prints error msg and returns NULL
 * Asserts: asserts given linked list is not Null
 * ---------------------------------------------------------------------
 */
Data* remove_front_list(List *list) {
	assert(list);
	if (list->size == 0 || list->head == NULL) {
		printf("Error(remove_front_list): list is empty\n");
		return NULL;
	}
	Node *temp = NULL;
	Data *d = NULL;
	temp = list->head;
	d = copy_data(list->head->data);
	list->head = list->head->next;
	free(temp);
	return d;
}

/**
 * ---------------------------------------------------------------------
 * Parameters: a pointer to a linked list (List*)
 * Returns: minimum data (Data*)
 * Description: returns copy of minimum data stored in list
 * if list is empty, prints error msg and returns NULL
 * Asserts: asserts given linked list is not Null
 * ---------------------------------------------------------------------
 */
Data* min_list(List *list) {
	assert(list);
	if (list->size == 0 || list->head == NULL) {
		printf("Error(min_list): list is empty\n");
		return NULL;
	}
	Node *min = list->head;
	Node *current = list->head;
	while (current != NULL) {
		if (compare_data(min->data, current->data) == 1) {
			min = current;
		}
		current = current->next;
	}
	return copy_data(min->data);
}

/**
 * ---------------------------------------------------------------------
 * Parameters: a pointer to a linked list (List*)
 * Returns: a pointer to a linked list (List*)
 * Description: returns copy of linked list
 * Asserts: asserts given linked list is not Null
 * ---------------------------------------------------------------------
 */
List* copy_list(List *list1) {
	List *list2 = create_list();
	assert(list1);
	if (list1->size == 0) {
		return list2;
	}
	Node *current = list1->head;
	while (current != NULL) {
		append_list(list2, current->data);
		current = current->next;
	}
	return list2;
}

