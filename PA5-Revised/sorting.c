//
// Created by Jose Luis Tejada on 2019-04-04.
//
#include "sorting.h"

//Function Declarations
static void Quick_Sort_Helper(long *input_array, int lb, int ub, int size);
static int partition(long *input_array, int lb, int ub, int size);
static int pivot(long *input_array, int lb, int ub, int size);
static void insertion_sort(long *input_array, int lb, int ub);
static void Merge_Sort_Helper(long *array, long* aux_arr, int lb, int ub);
static void merge(long *array, long *array_aux, int lb, int mid, int ub);
static int Check_Equal(long *input_array, int size);
//static void check_sorting(long *input_array, int size);

///////////////////////
//Mergesort Functions//
//////////////////////

//Valgrind Error in Mergesort, Make Correct
//Use Provided Mergesort Code

int Merge_Sort(long *array, int size){
    //Call auxilary memory helper
    long *aux_arr = malloc(sizeof(long) * size);
    if(aux_arr == NULL){
        printf("Auxilary array Memory Allocation Error\n");
        return  -1;
    }
    //Copy Contents
    for (int i = 0; i < size; ++i) {
        aux_arr[i] = array[i];
    }

    //Do Mergesort
    Merge_Sort_Helper(aux_arr, array,0, size);
//    printf("Checking now..\n");
//    check_sorting(array, size);
//    printf("Done\n");
    free(aux_arr);
    return 1;
}

static void Merge_Sort_Helper(long* aux_arr,long *array, int lb, int ub){ //eIterative Implementation
    if((ub-lb) <= MIN_SIZE_SORT){
        insertion_sort(array, lb, ub);
        return;
    }
    int mid = (lb+(ub-lb)/2);
    //Swap Roles of Auxilary and original array
    Merge_Sort_Helper(array, aux_arr, lb, mid);
    Merge_Sort_Helper(array, aux_arr, mid, ub);
    //Merge onto auxilary array
    merge(aux_arr,array,lb, mid, ub);

}

static void merge(long *array, long *array_aux, int lb, int mid, int ub){
    if((ub-lb) <= MIN_SIZE_SORT){
        insertion_sort(array_aux, lb, ub);
        return;
    }

    int i_index = lb; //Lower Array Index
    int j_index = mid; //Upper Array Index

    for (int k = lb; k < ub; k++) { //Elements in left and  right subarrays merged into array
        if (i_index >= mid){ //Copy Remaining Elements into array if lower subarray is reached.
            memcpy(&array_aux[k], &array[j_index], sizeof(long) * (ub - j_index + 1));
            return;
        } else if (j_index >= ub){ //Copy Remaining Elements into array if upper subarray is reached.
             memcpy(&array_aux[k], &array[i_index], sizeof(long) * (mid - i_index + 1));
            return;
        }else if(array[j_index] < array[i_index]){
            array_aux[k] = array[j_index++];
        }
        else{
            array_aux[k] = array[i_index++];
        }
    }

}

///////////////////////
//Quicksort Functions//
//////////////////////
void Quick_Sort(long *input_array, int size){
    Quick_Sort_Helper(input_array, 0, size - 1, size);
//    printf("Checking now..\n");
//    check_sorting(input_array, size);
//    printf("Done\n");
}

static void Quick_Sort_Helper(long *input_array, int lb, int ub, int size){ //With Tail Recursion
    int partition_index = 0;
    while(MIN_SIZE_SORT < (ub - lb)){
        partition_index = partition(input_array, lb, ub, size);
        if(partition_index == -1){ //Equal Elements
            return;
        }
        if(partition_index < (lb+(ub-lb)/2)){ //Determine smaller half to iterate
            Quick_Sort_Helper(input_array, lb, partition_index-1, size);
            lb = partition_index+1;
        }
        else{
            Quick_Sort_Helper(input_array, partition_index+1, ub, size);
            ub = partition_index-1;
        }
    }
    if(MIN_SIZE_SORT >= (ub - lb)){
        insertion_sort(input_array, lb, ub);
    }
}

static int partition(long *input_array, int lb, int ub, int size){
    //Pick a Pivot
    int pivot_index = pivot(input_array,lb,ub, size);
    if(pivot_index == -1){ //Equal Elements
        return -1;
    }
    long pivot_element = input_array[pivot_index];
    //Insertion Sort Optimization
    if ((ub - pivot_index) <= MIN_SIZE_SORT){
        insertion_sort(input_array, pivot_index, ub);
        //Select new pivot for remainder of program
        pivot_index = pivot(input_array,lb,pivot_index-1, size);
        pivot_element = input_array[pivot_index];
    }
    else if((pivot_index - lb) <= MIN_SIZE_SORT){
        insertion_sort(input_array, lb, pivot_index);
        //Select new pivot for remainder of program
        pivot_index = pivot(input_array,pivot_index+1,ub, size);
        pivot_element = input_array[pivot_index];
    }

    //Move Pivot to beggining
    long temp = input_array[lb];
    input_array[lb] = pivot_element;
    input_array[pivot_index] = temp;

    //Partition the Subarray
    int down = lb;
    int up = ub;
    long swap = 0;
    while(down < up){
        while((input_array[down] <= pivot_element) && (down < up)){
            down++;
        }
        while(input_array[up] > pivot_element){
            up--;
        }
        if(down < up){
            //Swap Elements
            swap = input_array[down];
            input_array[down] = input_array[up];
            input_array[up] = swap;
        }
    }
    input_array[lb] = input_array[up];
    input_array[up] = pivot_element;

    return up;
}

static int pivot(long *input_array, int lb, int ub, int size){
    int int1 = (rand() % (ub - lb + 1)) + lb;
    int int2 = (rand() % (ub - lb + 1)) + lb;
    int int3 = (rand() % (ub - lb + 1)) + lb;

    long val_1 = input_array[int1];
    long val_2 = input_array[int2];
    long val_3 = input_array[int3];

    //Repeated Elements Check
    if((val_1 == val_2) && (val_2 == val_3) && Check_Equal(input_array, size)){
        return -1;
    }

    //Chooses Median Pivot
    if(val_1 < val_2){
        if(val_2 < val_3){
            return int2;
        }
        else if(val_1 < val_3){
            return int3;
        }
        else{
            return int1;
        }
    }
    else if(val_3 < val_2){
        return int2;
    }
    else if(val_3 < val_1){
        return int3;
    }
    else{
        return int1;
    }
}

static void insertion_sort(long *input_array, int lb, int ub){
    int i, j;
    long key;
    for (i = lb + 1; i < (ub + 1); i++) {
        key = input_array[i];
        j = i - 1;
        while (j >= 0 && input_array[j] > key) {
            input_array[j + 1] = input_array[j];
            j = j - 1;
        }
        input_array[j + 1] = key;
    }
}

////////////////////
//Helper Functions//
////////////////////
//static void check_sorting(long *input_array, int size){
//    for (int i = 1; i < size ; ++i) {
//        if(input_array[i] < input_array[i-1]){
//            printf("Error at Index: %d, %ld < %ld \n", i,input_array[i],input_array[i-1]);
//        }
//    }
//    return;
//}

static int Check_Equal(long *input_array, int size){
    for (int i = 1; i < size ; ++i) {
       if(input_array[i] != input_array[i-1]){
           return 0;
       }
    }
    return  1;
}
