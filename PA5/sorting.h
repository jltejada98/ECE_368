//
// Created by Jose Luis Tejada on 2019-04-04.
//

#ifndef PA5_SORTING_H
#define PA5_SORTING_H
//Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


//Defnitions
#define MIN_SIZE_SORT 100
#define MIN_MERGE 15

//Function Declarations
long *Array_Load_From_File(char *filename, int *size);
int Array_Save_To_File(char *filename, long *array, int size);
void Quick_Sort(long *input_array, int size);
void Quick_Sort_Helper(long *Array, int lb, int ub, int size);
int partition(long *input_array, long pivot_element, int low, int high);
long pivot(long *input_array, int lb, int ub);
void insertion_sort_qc(long * input_array, int ub);
int check_sorting(long *input_array, int *size);
void Merge_Sort(long *Array, int Size);
void Merge_Sort_Helper(long *Array, long* aux_arr, int low, int high);
void merge(long *array_a, long *array_aux, int low, int mid, int high);
int minimum(int x, int y);

#endif //PA5_SORTING_H
