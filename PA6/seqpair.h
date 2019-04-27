//
// Created by Jose Luis Tejada on 2019-04-15.
//

#ifndef PA6_SEQPAIR_H
#define PA6_SEQPAIR_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

typedef struct rectangle{
    int label;
    double width;
    double height;
    double x;
    double y;
    int indegree_x;
    int indegree_y;
    struct rectangle *next;
}rect;

//Function Declarations
rect * load_input(FILE * fptr, int ** seq_1, int ** seq_2, int * num_rect);
//int Process_Input(int * seq_1, int * seq_2, rect * rectangle_array, rect *rectangle_copy, int * index_1, int *index_2, int size);
int Process_Input_Horizontal(int * seq_1, int * seq_2, rect * rectangle_array, int * index_1, int *index_2, int size);
int Process_Input_Vertical(int * seq_1, int * seq_2, rect * rectangle_array, int * index_1, int *index_2, int size);
void DFS_Horizontal(rect * rectangle_horiz, int size);
void dfs_horizontal(rect *rectangle_horiz, int rect_index, double distance);
void DFS_Vertical(rect * rectangle, int size);
void dfs_vertical(rect *rectangle_array, int rect_index, double distance);
int write_to_file(rect* rectangle_horizontal, rect * rectangle_vertical, FILE *fptr, int size);
void Pre_Processing(int ** seq_1, int ** seq_2, int ** index_sequence_1, int ** index_sequence_2, int size);
rect * Pre_Processing_Rectangles(rect * rectangle, int size);
rect * Add_Edge(rect rect_node);
void free_rectangle_array(rect * rectangle, int size);
int cmpfunc_x (const void * a, const void * b);


#endif //PA6_SEQPAIR_H
