/*
 * ---------------------------------
 * Student Name: Maham Farooq
 * Student ID: 
 * Student Email: 
 * ---------------------------------
 */

# include <stdio.h>
# include <string.h>
# include <ctype.h>
# include <math.h>
# include <stdlib.h>
# include "A4.h"

//-------------------------Task 1 ----------------------------

void format_city(char *city) {

	int len = strlen(city);

	int i, index = 0;
	city[0] = toupper(city[0]);
//	printf("First Letter%c", city[0]);

	for (i = 0; i < len; i++) {
		if (city[i] == ' ') {
			break;

		}
		index++;
	}

	for (i = index; i < len; i++) {
		city[i] = city[i + 1];
	}
	city[index] = toupper(city[index]);

	return;
}

void format_cities(char city_array[][MAX], const int size) {

	if (!city_array || !*city_array) { // check whether pointer is NULL and string is empty
		printf("Error(format_cities): array is NULL\n");
		return;
	}
	if (size <= 0) {
		printf("Error(format_cities): invalid size\n");
		return;
	}

	int i;

	for (i = 0; i < size; i++) {
		city_array[i][0] = toupper(city_array[i][0]);
		city_array[i][MAX] = *(city_array[i] + MAX);
		format_city(&(city_array[i][MAX]));

	}

	return;
}

//-------------------------Task 2 ----------------------------

void format_str(const char *inStr, char *outStr) {
	int i, size;
	char temp2;
	int pos2 = 0;
	char temp1;
	int pos1;

// string length
	size = strlen(inStr);
	printf("	String Length = %d\n", size);
	strcpy(outStr, inStr);

// middle caps
	for (i = 0; i < size; i++)
		outStr[i] = tolower(inStr[i]);
	if (size > 1) {
		for (i = 1; i < size - 1; i++) {

			outStr[i] = toupper(inStr[i]);
		}
	}
	printf("	After middle caps = %s\n", outStr);

// split
	for (i = size - 1; i >= size / 2; i--) {
		outStr[i + 1] = outStr[i];
	}
	outStr[size / 2] = ' ';
	printf("	After split = %s\n", outStr);

// reverse left side
	i = (size / 2) - 1;

	while (i > pos2) {
		temp2 = outStr[i];
		outStr[i--] = outStr[pos2];
		outStr[pos2++] = temp2;
	}
	printf("	After First half reverse = %s\n", outStr);

// reverse right side
	pos1 = (size / 2) + 1;
	i = size;

	while (i > pos1) {
		temp1 = outStr[i];
		outStr[i--] = outStr[pos1];
		outStr[pos1++] = temp1;
	}
	printf("	After Second half reverse = %s\n", outStr);
	return;
}

//-------------------------Task 3 ----------------------------

int* get_multiples_array1(int *multiples, const int size) {
	if (!multiples) {		// same as array == NULL
		printf("Error(get_multiples_array1): invalid array\n");
		return NULL;

	}

	if (size <= 0) {
		printf("Error(get_multiples_array1): invalid size\n");
		return NULL;
	}

	int row = size, col = 10;

	int *array = (int*) malloc(row * col * sizeof(int));

	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			*(array + i * col + j) = multiples[i] * (j + 1);

	return array;
}

void print_multiples1(int *array, const int size) {
	if (!array) {		// same as array == NULL
		printf("Error(print_multiples1): invalid array\n");
		return;
	}

	if (size <= 0) {
		printf("Error(print_multiples1): invalid size\n");
		return;
	}

	int row = size, col = 10;

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (*(array + i * col + j) == *(array + i * col + (col - 1))) {
				if (*(array + i * col + j) > 0
						&& *(array + i * col + j) < 1000) {
					printf("%3d", *(array + i * col + j));
				} else
					printf("  0");
			} else {
				if (*(array + i * col + j) > 0
						&& *(array + i * col + j) < 1000) {
					printf("%3d ", *(array + i * col + j));
				} else
					printf("  0 ");
			}
		}
		printf("\n");
	}

	return;
}

//-------------------------Task 4 ----------------------------
int** get_multiples_array2(int *multiples, const int size) {
	if (!multiples) {		// same as array == NULL
		printf("Error(get_multiples_array2): invalid array\n");
		return NULL;

	}

	if (size <= 0) {
		printf("Error(get_multiples_array2): invalid size\n");
		return NULL;
	}
//	int row = size, col = 10, len = 0;
	int row = size, col = 10;
	int **array = (int**) malloc(row * sizeof(int*));
//	int *ptr;
	int i, j;

	for (i = 0; i < row; i++)
		array[i] = (int*) malloc(col * sizeof(int));

	// method 4
//	len = sizeof(int*) * row + sizeof(int) * col * row;
//	array = (int**) malloc(len);
//	ptr = (int*) (array + row);	// ptr pointing to first element in 2d array
//
//	for (i = 0; i < row; i++)
//		array[i] = (ptr + col * i);

	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++)
			array[i][j] = multiples[i] * (j + 1); // OR *(*(arr+i)+j)
	}

//	for (i = 0; i < row; i++) {
//		for (j = 0; j < col; j++) {
//			if (array[i][j] == array[i][col - 1]) {
//				if (array[i][j] > 0 && array[i][j] < 1000) {
//					printf("%3d", array[i][j]);
//				} else
//					printf("  0");
//			} else {
//				if (array[i][j] > 0 && array[i][j] < 1000) {
//					printf("%3d ", array[i][j]);
//				} else
//					printf("  0 ");
//			}
//		}
//		printf("\n");
//	}

	return array;
}

void print_multiples2(int **array, const int size) {
	if (!array) {		// same as array == NULL
		printf("Error(print_multiples2): invalid array\n");
		return;
	}

	if (size <= 0) {
		printf("Error(print_multiples2): invalid size\n");
		return;
	}
	int row = size, col = 10;
	int i, j;
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			if (array[i][j] == array[i][col - 1]) {
				if (array[i][j] > 0 && array[i][j] < 1000) {
					printf("%3d", array[i][j]);
				} else
					printf("  0");
			} else {
				if (array[i][j] > 0 && array[i][j] < 1000) {
					printf("%3d ", array[i][j]);
				} else
					printf("  0 ");
			}
		}
		printf("\n");
	}
	return;
}
