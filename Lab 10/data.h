/*
 -------------------------------------
 File:    data.h
 Project: R9
 file description
 -------------------------------------
 Author:  your name here
 ID:      your ID here
 Email:   your Laurier email here
 Version  2021-07-05
 -------------------------------------
 */

#ifndef DATA_H_
#define DATA_H_
# include "process.h"
typedef int Data;

void print_data(Data *d);
void print_data_array(Data *array, const int size);
void destroy_data(Data **d);
Data* copy_data(Data *d);
void swap_data(Data *d1, Data *d2);
int compare_data(Data *d1, Data *d2);

#endif /* DATA_H_ */
