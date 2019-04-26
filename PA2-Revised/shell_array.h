//
// Created by Jose Luis Tejada on 2019-03-25.
//

#ifndef PA2_REVISED_SHELL_ARRAY_H
#define PA2_REVISED_SHELL_ARRAY_H

long *Array_Load_From_File(char *filename, int *size);
int Array_Save_To_File(char *filename, long *array, int size);
void Array_Shellsort(long *array, int size, double *n_comp);

#endif //PA2_REVISED_SHELL_ARRAY_H
