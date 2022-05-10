/*
 -------------------------------------
 File:    process.h
 Project: R7
 file description
 -------------------------------------
 Author:  Maham Farooq
 ID:      200498180
 Email:   faro8180@mylaurier.ca
 Version  2021-06-22
 -------------------------------------
 */

// pound symbol = pre-processor director --> processed by C environment before compilation
#ifndef PROCESS_H_	// if not defined already, define process_h
// need to define this because it will cause internal conflict since everything will be scrambled
#define PROCESS_H_
// source --> editor (multiple stages during building of project):
//pre-processing --> preprocessor - looks for everything that has # and prepare first
// e.g. define MAX 100
// compilation --> compiler - takes C code and translates to assembly code
// --> assembler - convert assembly code to binary
// --> linker - connect all steps together to have executable
// --> loader - once executable, to run, you use loader

//// what to include in header files --> can use any of these functions in header file anywhere
/// constants
/// function prototypes: just want overall gist of function (function name and parameter type)
/// 	e.g. int factorial(int); -- .c files will give more detail about it

# define True 1
# define False 0

// defining a new type
typedef struct {
	// anything put inside will be a variable not functions (for now at least)
	unsigned long PID; // process ID (10-digit)
	unsigned int time; // requested processing time/ service time (don't want neg value so unsigned)
	unsigned int arrival;	// timestamp of arrival time of process

} Process;

// to access data and define structures
//Process p;
//p.PID = ...
//p.time = ...

Process* create_process(long p_pid, int p_time, int arrival_time);// return value will be a process
// however, rmr that anything created inside functino will be destroyed once out
// so to keep it, must use malloc --> malloc also returns a process pointer
// must remember to do garbage collection
void destroy_process(Process **p);// garbage collection to take prev line and make it NULL
void print_process(Process *p);
Process* copy_process(Process *p);
void get_process_info(Process *p, char *info);// allows us to have string rep of structure
int is_equal_process(Process *p1, Process *p2);
unsigned long get_UPID(); // Utility function (universal ID) --> function will generate unique ID that will not repeat anywhere in code

#endif /* PROCESS_H_ */
