//
// Created by Jose Luis Tejada on 2019-03-25.
//

#include "shell_array.h"
#include "sequence.h"
#include <stdio.h>
#include <stdlib.h>


long *Array_Load_From_File(char *filename, int *size)
{
    FILE *file_ptr = fopen(filename, "r");

    if (file_ptr == NULL)
    {
        printf("Error Opening Input File (Array)\n");
        *size = 0;
        return NULL;
    }

    //Determination of size of input file
    fseek(file_ptr, 0, SEEK_END);
    long file_size = ftell(file_ptr);
    *size = (file_size / sizeof(long));

    //If file empty do we allocate memory anyways?
    if (*size == 0)
    {
        return NULL;
    }


    //Allocating Memory for array
    long *file_array = malloc(sizeof(long) *  (*size) );

    if (file_array == NULL)
    {
        printf("Error Allocating Input Array Memory\n");
        *size = 0;
        return NULL;
    }

    //Reading File
    fseek(file_ptr, 0, SEEK_SET);
    int longs_read = fread(file_array, sizeof(long), (*size), file_ptr);

    if (longs_read != (*size))
    {
        printf("Error Reading Input File\n");
        *size = 0;
        return NULL;
    }

    fclose(file_ptr);

    return file_array;
}

int Array_Save_To_File(char *filename, long *array, int size)
{
    FILE *file_ptr = fopen(filename, "w");

    if (file_ptr == NULL)
    {
        printf("Error Opening Output File\n");
        return 0;
    }
    //Write to Array
    int num_written = fwrite(array, sizeof(long), size, file_ptr);

    fclose(file_ptr);

    return num_written;
}

void Array_Shellsort(long *array, int size, double *n_comp)
{
    //Sequence Generation
    int seq_size = 0;
    long *sequence = Generate_2p3q_Seq(size, &seq_size);

    if (sequence == NULL)
    {
        printf("Error Generating Sequence\n");
        return;
    }

    //Shell Sort Implementation
    long temp_r = 0;
    long current_k = 0;
    long i = 0;

    for (int k = (seq_size - 1); k >= 0; --k) //for each k (in descending order)
    {
        current_k = sequence[k];
        for (int j = current_k; j <= (size - 1); ++j) //for j ← k to n-1
        {
            temp_r = array[j];
            i = j;
            ++(*n_comp);
            while((i>=current_k) && (array[i - current_k] > temp_r))
            {
                array[i] = array[i - current_k];
                i = i - current_k;
                ++(*n_comp);
            }
            array[i] = temp_r;
        }
    }

    free(sequence);
}
