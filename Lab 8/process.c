/*
 * ---------------------------------
 * Student Name: Maham Farooq
 * Student ID: 200498180
 * Student Email: faro8180@mylaurier.ca
 * ---------------------------------
 */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <assert.h>
# include "process.h"	// double " means header created by user while <> means standard built in library

Process* create_process(long pid, int time, int arrival) {
	Process *p = (Process*) malloc(sizeof(Process));

	// set time
	if (time <= 0) {
		fprintf(stderr, "Error(create_process): invalid time - set to 0\n"); // different method of printing
		// stderr prints to standard error console (in red) but it's not buffered
		p->time = time;
	} else
		p->time = time;	// if process is a pointer, if not pointer use '.' (ex. p.time)

	if (arrival < 0) {
		fprintf(stderr,
				"Error(create_process): invalid arrival time - set to 0\n");
		p->arrival = arrival;
	} else
		p->arrival = arrival;

	if (pid <= 0) {
		fprintf(stderr, "Error(create_process): invalid pid - set to random\n");
		p->PID = get_UPID();
	} else
		p->PID = pid;	// line included only for purpose of testing
	return p;
}

void destroy_process(Process **p) {

	assert(*p != NULL);	// assert error will force program to stop
	(*p)->PID = 0;
	(*p)->time = 0;
	(*p)->arrival = 0;

	free(*p); 	// have double pointer so must be freed
	*p = NULL;
	return;

// explanation example
//	int *ptr;
//	free(ptr);
//	ptr = NULL;	// set to NULL b/c u can't free memory that u allocated in memeory using malloc twice
}

void print_process(Process *p) {
	assert(p!=NULL);
	char info[30];
	strcpy(info, "");
	get_process_info(p, info);
	printf("%s", info);
	return;
}

Process* copy_process(Process *p1) {
	assert(p1 != NULL);
	Process *p2 = (Process*) malloc(sizeof(Process));
	p2->PID = p1->PID;
	p2->time = p1->time;
	p2->arrival = p1->arrival;
	return p2;

}

void get_process_info(Process *p, char *info) {
	assert(p!=NULL);
	char process[30];
	sprintf(process, "[%u](%lu,%u)", p->arrival, p->PID, p->time);
	strcpy(info, process);
	return;
}

int is_equal_process(Process *p1, Process *p2) {
	assert(p1 != NULL && p2 != NULL);
	if (p1->PID != p2->PID)
		return False;
	if (p1->time != p2->time)
		return False;
	return True;

}

unsigned long get_UPID() {
	static int counter = 10000;
// static data members - variable will be called in memory and be preserved
// global variable and will return the value in function

// get higher 5 digits
	unsigned long higher5 = rand() % (39999 - 10000 + 1) + 10000;
	higher5 = higher5 * 10000;
	int lower5 = counter;
	counter++;
	return higher5 + lower5;

}
