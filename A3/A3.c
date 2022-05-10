/**
 * -------------------------
 * Student Name: Maham Farooq
 * Student ID:
 * Student email:
 * -------------------------
 */
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "A3.h"

/**
 * -------------------------------------------------------------------
 * Parameters:
 * 	  array: a pointer to an array of integers (int*)
 * 	  size: size of an array (const int)
 * returns:
 * 	  last: pointer to last element that is sandwiched between its multiples (int*)
 * Description:
 *    Searches for a number that is sandwiched between its multiples
 *    If multiple numbers exist, then a pointer to the last one is returned.
 *    prints an error message and returns a NULL pointer if array pointer is NULL
 *    	or given size is non-positive
 * -------------------------------------------------------------------
 */
int* sandwich(int *array, const int size) {
	if (0 < size && size <= 2) {
		return NULL;
	}
	if (size <= 0) {
		printf("Error(sandwich): Invalid array size\n");
		return NULL;
	}

	if (array == NULL) {
		printf("Error(sandwich): Input array is NULL\n");
		return NULL;
	}

	int previous;
	int ahead;
	int *ptr = NULL;
	int i = 1;
	int current;
//	ahead++;

//	previous = *array;
	array++;

	for (i = 1; i < size - 1; i++) {
//	while (i < size || *array < size || *ahead < size) {
		array--;
		previous = *array;
		array++;
		current = *array;
		array++;
		ahead = *array;
		array--;

//		array++;
//		printf("%d\n", i);
//		printf("Prev: %d\n", previous);
//		printf("Curr: %d\n", current);
//		printf("Ahead: %d\n", ahead);

		if ((previous % current == 0) && ((ahead % current == 0))) {
//			printf("hello");
			ptr = array;
		}

		array++;

	}

	return ptr;
}

/**
 * -------------------------------------------------------------------
 * Parameters:
 * 		array: a generic pointer to an array (void*)
 * 		size: size of an array (const int)
 * 		mode: character representing array type (char)67
 * 				'C' --> character array
 * 				'L' --> integer array
 * 				'D' --> double array
 * returns:
 * 		None
 * Description:
 *    Prints contents of an array with formatting depending on printing mode
 *    Mode 1: chars "StringAppearHere"
 *    Mode 2: long { v1 , v2 , v3 , ... }
 *    Mode 3: double { v1.000 , v2.000 , v3.000 , ... }
 *    If size is <= 0 for any type --> print { }
 *    if invalid mode --> print error
 * -------------------------------------------------------------------
 */
void print_array(void *arrayPtr, const int size, char mode) {
//	int i;
	char *myPtrC = NULL;
	long *myPtrI = NULL;
	double *myPtrD = NULL;

	if (size <= 0) {
		printf("{ }\n");
		return;
	}

	switch (mode) {
	case 'C':
		myPtrC = (char*) malloc(sizeof(char));
		myPtrC = arrayPtr;

		printf("\"");
		for (int i = 0; i < size - 1; i++) {
			printf("%c", *(myPtrC));
			myPtrC++;
		}
		printf("\"\n");

		break;
	case 'L':
		myPtrI = (long*) malloc(sizeof(long));
		myPtrI = arrayPtr;

		printf("{");
		for (int i = 0; i < size - 1; i++) {
			printf(" %ld ,", *(myPtrI));
			myPtrI++;
		}
		printf(" %ld }\n", *(myPtrI));
		break;
	case 'D':
		myPtrD = (double*) malloc(sizeof(double));
		myPtrD = arrayPtr;

		printf("{");
		for (int i = 0; i < size - 1; i++) {
			printf(" %.3lf ,", *(myPtrD));
			myPtrD++;
		}
		printf(" %.3lf }\n", *(myPtrD));

		break;

	default:
		printf("Error(print_array): unsupported mode\n");

	}
//	free(arrayPtr);
//	free(myPtrI);
//	free(myPtrD);

	return;
}

/**
 * -------------------------------------------------------------------
 * Parameters:
 * 	  array: a pointer to an array of integers (int*)
 * 	  size: size of an array (const int)
 * returns:
 * 	  ptr: pointer to the element that is equal or closest to average (int*)
 * Description:
 *    1- Finds the average of the values within the array and print it to the console.
 *    2- The average is �ceiled�, i.e. rounded to the upper integer value.
 *    3- Search the array for an element that is equal to the average,
 *      and return a pointer to that element.
 *    4- If there are multiple values equal to the average, a pointer to the
 *      first element that equals to average is returned.
 *    5- If no value is equal to the average, a pointer to the value
 *      closest to the average is returned.
 *    6- prints an error message and returns a NULL pointer if array pointer is NULL
 *    	or given size is non-positive
 * -------------------------------------------------------------------
 */
int* find_avg_element(int *array, const int size) {
	int i, j;
	double sum = 0;
	int *original = array;
	double average;
	if (size <= 0) {
		printf("Error (find_avg_element): Invalid array size\n");
		return NULL;
	}
	if (array == NULL) {
		printf("Error (find_avg_element): NULL pointer\n");
		return NULL;
	}
	for (i = 0; i < size; i++) {
		sum = sum + *(array++);
	}
	average = sum / size;
	printf("Average = %.1lf\n", average);
	array = original;
	for (j = 0; j < size - 1; j++) {
		if (*array == average) {
			break;
		} else if (*array > average) {
			break;
		}
		array++;
	}
	return array;
}

/**
 * -------------------------------------------------------------------
 * Parameters:
 * 	  array: a pointer to an array of long integers (long*)
 * 	  ptrs: an array of long pointers (long* [])
 * returns:
 * 	  No reutrns
 * Description:
 *    The pointer array stores some pointers to elements in the array
 *    Access the pointer array to print the following:
 *    1-	The index of that element in the array
 *    2-	The value of the element it points to
 *    3-	The value of the previous element
 *    4-	The value of the next element
 *    The maximum size for the pointer array is MAX, and the last item is NULL.
 * -------------------------------------------------------------------
 */
void print_ptr_array(long *array, long *ptrs[]) {
	int i;
	long previous;
	long current;
	long next;

	previous = *array;
//	next = array;
	next = *array;
//	printf("Count %d\n", count);
	printf("ArrayIndex   Previous     Current      Next         \n");
	for (i = 0; i < MAX; i++) {
		array--;
		previous = *array;
		array++;
		current = *array;
		array++;
		next = *array;
		array--;

		if (*array == 1 || *array == -4) {
			if (i == 0) {
				previous = -1;
			}
			if (i == 9) {
				next = -1;
			}
			printf(
					"%-2d           %-2ld           %-2ld           %-2ld           \n",
					i, previous, current, next);
		}
//		if (next == -1) {
//			break;
//		}
//		printf("Prev: %ld\n", previous);
//		printf("Curr: %ld\n", current);
//		printf("Next: %ld\n", next);
//		previous++;
//		current++;
//		next++;
		array++;
	}
	return;
}
