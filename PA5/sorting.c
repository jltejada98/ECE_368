//
// Created by Jose Luis Tejada on 2019-04-04.
//
#include "sorting.h"


///////////////////////
//Mergesort Functions//
//////////////////////
void Merge_Sort(long *Array, int Size){
    //Call mergesort helper
    long *aux_arr = malloc(sizeof(long) * Size);
    Merge_Sort_Helper(Array,aux_arr, 0, Size - 1);
    free(aux_arr);
}

void Merge_Sort_Helper(long *Array, long* aux_arr, int low, int high){
    //Iterative Implementation
    int size = 1;
    int i = 0;
    while(size < (high+1)){
        i = 0;
        while(i < (high - size)){
            if(i % 2 == 0){
                merge(aux_arr, Array, i, i+size - 1, minimum(i+2*size - 1, high));
            }
            else{
                merge(Array, aux_arr, i, i+size - 1, minimum(i+2*size - 1, high));
            }
            i = i + 2*size;
        }
        size = 2* size;
    }

}

int minimum(int x, int y){
    return (x < y) ? x : y;
}

void merge(long *array_a, long *array_aux, int low, int mid, int high){
    memcpy(&array_aux[low], &array_a[low], mid-low + 1);
    memcpy(&array_aux[mid+1], &array_a[mid + 1], high-mid);
    int i = low;
    int j = mid + 1;
    for (int k = low; k < high; ++k) {
        if(i < mid){
            array_a[k] = array_aux[j++];
        }
        else if(j > high){
            array_a[k] = array_aux[i++];
        }
        else if(array_aux[j] < array_aux[i]){
            array_a[k] = array_aux[j++];
        }
        else{
            array_a[k] = array_aux[i++];
        }
    }
}




///////////////////////
//Quicksort Functions//
//////////////////////
void Quick_Sort(long *input_array, int size){
    Quick_Sort_Helper(input_array, 0, size - 1, size);
    insertion_sort_qc(input_array, size - 1);
}

void Quick_Sort_Helper(long *input_array, int lb, int ub, int size){ //With Tail Recursion
    while((ub - lb + 1) > MIN_SIZE_SORT){
        long pivot_element = pivot(input_array,lb,ub);
        int partition_index = partition(input_array, pivot_element, 0, size - 1);
//        printf("%d\n", partition_index);
        if(partition_index < (lb+(ub-lb)/2)){
            Quick_Sort_Helper(input_array, lb, partition_index, size);
            lb = partition_index + 1;
        }
        else{
            Quick_Sort_Helper(input_array, partition_index + 1, ub, size);
            ub = partition_index - 1;
        }
    }
}

int partition(long *input_array, long pivot_element, int low, int high){ //Three way partitioning.
    int mid_ind= 0;
    long mid_val = 0;
    while(mid_ind < (high)){
        mid_val = input_array[mid_ind];
        if(mid_val < pivot_element){
            input_array[mid_ind] = input_array[(low)];
            input_array[(low)] = mid_val;
            ++(low);
            ++mid_ind;
        }
        else if(mid_val == pivot_element){
            ++mid_ind;
        }
        else{ //mid_val > pivot
            input_array[mid_ind] = input_array[(high) - 1];
            input_array[(high) - 1] = mid_val;
            -- (high);
        }
    }

    return low;
}

long pivot(long *input_array, int lb, int ub) {
    long int_1 = input_array[rand() % (ub + 1 - lb) + lb];
    long int_2 = input_array[rand() % (ub + 1 - lb) + lb];
    long int_3 = input_array[rand() % (ub + 1 - lb) + lb];

    //Chooses Median Pivot
    if(int_1 < int_2){
        if(int_2 < int_3){
            return int_2;
        }
        else if(int_1 < int_3){
            return int_3;
        }
        else{
            return int_1;
        }
    }
    else{
        if(int_1 < int_3){
            return int_1;
        }
        else if(int_2 < int_3){
            return int_3;
        }
        else{
            return int_2;
        }
    }
}

void insertion_sort_qc(long * input_array, int ub){
    long val;
    int index;
    for (int i = 1; i < (ub + 1); ++i) {
        val = input_array[i];
        index = i - 1;
        while ((index >= 0) && (input_array[index] > val)){
            input_array[index + 1] = input_array[index];
            --index;
        }
        input_array[index+1] = val;
    }

}

////////////////////
//Helper Functions//
////////////////////
int check_sorting(long *input_array, int *size){
    for (int i = 1; i < *size ; ++i) {
        if(input_array[i] < input_array[i-1]){
            return 0;
        }
    }
    return 1;
}