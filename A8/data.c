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

int compare_data(Data *d1, Data *d2) {
	if (d1->arrival < d2->arrival)
		return 2;
	else if (d1->arrival > d2->arrival)
		return 1;
	else if (d1->arrival == d2->arrival) {
		if (d1->time < d2->time)
			return 2;
		else if (d1->time > d2->time)
			return 1;
		else if (d1->time == d2->time) {

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
