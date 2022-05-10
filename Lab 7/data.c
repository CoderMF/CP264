/*
 * ---------------------------------
 * Student Name: Maham Farooq
 * Student ID: 200498180
 * Student Email: faro8180@mylaurier.ca
 * ---------------------------------
 */

# include "data.h"

void print_data(Data *d) {
	print_process(d);
	return;
}

void destroy_data(Data **d) {
	destroy_process(d);
	return;
}

Data* copy_data(Data *d) {
	return copy_process(d);
}
