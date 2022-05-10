/*
 * ---------------------------------
 * Student Name: Maham Farooq
 * Student ID: 200498180
 * Student Email: faro8180@mylaurier.ca
 * ---------------------------------
 */

# include <stdio.h>
# include "matrix.h"
# include "A2.h"

//-----------------------------------------------------------------------
/**
 * Parameters:		None
 * return:			True(1)/False(0)
 * Description:
 * 		inspect the current contents of matrix
 * 		return True if the contents represent a valid square matrix
 * 		A square matrix is a matrix which the number of rows is the same as the number of columns
 * 		Note that an empty matrix is a square matrix of size 0x0
 **/

int get_column_length(int i);
int get_row_length(int j);

int is_square() {
	is_empty();
	int col;
	int row;
	int i;

	if (is_empty()) {
		return True;
	} else if (!is_matrix()) {
		return False;
	} else {
		for (i = 0; i < SIZE; i++) {
			row = get_row_length(i);
			col = get_column_length(i);
			if (row != col) {
				break;
			}
		}
	}

	if (row != col) {
		return False;
	} else {
		return True;
	}

}

//-----------------------------------------------------------------------
/**
 * Parameters:		None
 * return:			True(1)/False(0)
 * Description:
 * 		inspect the current contents of matrix
 * 		return True if the contents represent a valid identity matrix
 * 		An identity matrix is a square matrix, all diagonal elements equal to 1,
 * 			all other elements equal to 0
 * 		Note that an empty matrix is NOT an identity matrix
 */

int is_identity() {
	int i, j, check = 1;
	if (is_empty()) {
		return False;
	} else if (!is_matrix()) {
		return False;
	} else if (get_row_length(0) == 1 && get_column_length(0) == 1
			&& matrix[0][0] == 0) {	// case if there is only 1 element in matrix
		return False;
	} else {
		for (i = 0; i < SIZE; i++) {
			for (j = 0; j < SIZE; j++) {
				if (matrix[i][j] == 1 || matrix[i][j] == 0
						|| matrix[i][j] == -1) {
					check = 1;
				} else {
					check = 0;
					return False;
				}
			}
		}
	}
	if (check == 1) {
		return True;
	} else {
		return False;
	}

}
//---------------------------------------------------------
/**
 * Parameters:		None
 * return:			True(1)/False(0)
 * Description:
 * 		inspect the current contents of matrix
 * 		return True if the contents represent a valid uniform matrix
 * 		A uniform matrix is a matrix in which all elements are equal
 * 		Note that an empty matrix is NOT a uniform matrix
 */
int is_uniform() {
	int i, j, check = 1;
	if (is_empty()) {
		return False;
	} else if (!is_matrix()) {
		return False;
	} else {
		for (i = 0; i < SIZE; i++) {
			for (j = 0; j < SIZE; j++) {
				if (matrix[0][0] == matrix[i][j] || matrix[i][j] == -1) {
					check = 1;
				} else {
					check = 0;
					return False;
				}
			}
		}
		if (check == 1) {
			return True;
		} else {
			return False;
		}
	}
}
//---------------------------------------------------------
/**
 * Parameters:		None
 * return:			True(1)/False(0)
 * Description:
 * 		inspect the current contents of matrix
 * 		return True if the contents represent a valid unique matrix
 * 		A unique matrix is a matrix in which all elements have unique values
 * 			i.e. no two elements have equal value
 * 		Note that an empty matrix is NOT a unique matrix
 */

int is_unique() {
	int i, j;
	int check = 1;
	int row, col;
	if (is_empty()) {
		return False;
	} else if (!is_matrix()) {
		return False;
	} else if (get_row_length(0) == 1 && get_column_length(0) == 1) {
		return True;

//	} else if (get_row_length(0) == 1 || get_column_length(0) == 1) {
//		if (get_row_length(0) == 1) {
//			for (i = 0; i < get_row_length(0); i++) {
//				for (j = 0; get_column_length(0); j++) {
//					for (i = row + 1; i < get_row_length(0); i++) {
//
//					}
//				}
//			}
//		}
	} else {
//		printf("%d %d", get_row_length(0), get_column_length(0));
		for (row = 0; row < get_row_length(0); row++) {
			for (col = 0; col < get_column_length(0); col++) {
				for (j = col + 1; j < get_column_length(0); j++) {
//					printf("%d %d", matrix[row][col], matrix[row][j]);
					if (matrix[row][col] == -1 || matrix[row][j] == -1
							|| get_column_length(0) == 1) {
						break;
					} else {
						if (matrix[row][col] == matrix[row][j]) {

							check = 0;
							break;
						}
					}
				}
				for (i = row + 1; i < get_row_length(0); i++) {
//					printf("row %d %d\n", matrix[row][col], matrix[i][col]);
					if (matrix[row][col] == -1 || matrix[i][col] == -1
							|| get_row_length(0) == 1) {
						break;
					} else {
						if (matrix[row][col] == matrix[i][col]) {

							check = 0;
							break;
						}
					}
				}

			}
		}
	}
	if (check == 1) {
		return True;
	} else {
		return False;
	}
}

//---------------------------------------------------------
/**
 * Parameters:		None
 * return:			True(1)/False(0)
 * Description:
 * 		inspect the current contents of matrix
 * 		return True if the contents represent a valid symmetric matrix
 * 		A symmetric matrix is a matrix which equals to its transpose
 * 		Note that an empty matrix is a VALID symmetric matrix
 */
int is_symmetric() {
	int transpose[SIZE][SIZE];
	int i, j, check = 1;
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			transpose[i][j] = matrix[j][i];
		}
	}
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			if (matrix[i][j] != transpose[i][j]) {
				check = 0;
				break;
			}
		}
	}
	if (check == 1) {
		return True;
	} else {
		return False;
	}
}

//---------------------------------------------------------
/**
 * Parameters:		None
 * return:			True(1)/False(0)
 * Description:
 * 		inspect the current contents of matrix
 * 		return True if the contents represent a valid binary matrix
 * 		A binary matrix is a matrix which all of its elements are equal to either 1 or 0
 * 		Note that an empty matrix is NOT a binary matrix
 */
int is_binary() {
	int i, j, check = 1;
	if (is_empty()) {
		return False;
	} else if (!is_matrix()) {
		return False;
	} else {
		for (i = 0; i < SIZE; i++) {
			for (j = 0; j < SIZE; j++) {
				if (matrix[i][j] != 1 && matrix[i][j] != 0
						&& matrix[i][j] != -1) {
					check = 0;
					break;
				}
			}
		}
		if (check == 1) {
			return True;
		} else {
			return False;
		}
	}

}

//---------------------------------------------------------
/**
 * Parameters:		None
 * return:			True(1)/False(0)
 * Description:
 * 		inspect the current contents of matrix
 * 		return True if the contents represent a valid incremental matrix
 * 		An incremental matrix is:
 * 		a matrix which every element is greater than or equal to the one before it
 * 		Order: left to right, then top to bottom.
 */
int is_incremental() {
	int check = 1;
	int row, col;

	if (is_empty()) {
		return False;
	} else if (!is_matrix()) {
		return False;

	} else {
		for (row = 0; row < get_row_length(0); row++) {
			for (col = 0; col < get_column_length(0); col++) {
				if ((matrix[row][col] > matrix[row][col + 1])
						&& matrix[row][col + 1] != -1) {
					check = 0;
					break;
				}

			}
//			printf("%d %d\n", matrix[row][col], matrix[row + 1][0]);
			if (matrix[row][col] > matrix[row + 1][0]
					&& matrix[row + 1][0] != -1) {
				check = 0;
				break;
			}

		}
		if (check == 1) {
			return True;
		} else {
			return False;
		}
	}

}
