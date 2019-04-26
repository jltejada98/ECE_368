//
// Created by Jose Luis Tejada on 2019-03-25.
//

#ifndef PA3_REVISED_PA3_H
#define PA3_REVISED_PA3_H

//Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Structures
typedef struct TNode
{
    struct TNode* left;
    struct TNode* right;
    int label;
    double cap;
    double length_r;
    double length_l;
    double c_down;
    double r_path;
}TreeNode;


typedef struct Stack
{
    TreeNode **array;
    int capacity;
    int top;
}Stack;

///////////////////////////////
//// Function Declarations/////
///////////////////////////////

int Read_Header(FILE *file_ptr, double *r_source, double *r, double *c);
TreeNode * Create_Postorder(FILE *file_ptr, int newlines);
TreeNode * Create_Leaf_Node(int label, double capacitance);
TreeNode * Create_Middle_Node(double length_L, double length_R);
Stack * Create_Stack(int size);
void Push (Stack *input_stack, TreeNode *new_item);
TreeNode * Pop(Stack *input_stack);
void printPreorder(TreeNode* node, FILE *fptr, int num_nodes);
void Free_Tree_Helper(TreeNode *root_node);
void Determine_CR(TreeNode *node_i,double WL, double WC, double WR, double r_path);
void Determine_CD(TreeNode * node);
int Determine_Time_Delay(TreeNode * node, double time, FILE *file_ptr);

#endif //PA3_REVISED_PA3_H
