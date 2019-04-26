//
// Created by Jose Luis Tejada on 2019-03-07.
//

#ifndef PA4_PA3_H
#define PA4_PA3_H
//Include standard Libraries
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//Ask whether we can use limits and math libraries.
#include <limits.h>
#include <math.h>

//Consider adding height element to structure.

typedef struct TNode{
    struct TNode *left;
    struct TNode *right;
    int value;
    int balance;
    int height;
    int delete;
}TreeNode;

//Function Declarations
TreeNode * Build_Load_From_File(FILE *fptr, long *tree_size, int *op_flag);
void Build_Write_To_File(TreeNode *root, FILE *fptr);
TreeNode *insert_node(TreeNode *root, int key, long *tree_size);
TreeNode *delete_node(TreeNode *root, int key, long *tree_size);
TreeNode *Build_Tree(TreeNode *root, FILE *fptr, long ind, long size, int *read_successful);
int Evaluate_BST(TreeNode *root, int lower, int upper);
int Evaluate_Balance(TreeNode *root);
TreeNode *create_node(int value);
void free_tree(TreeNode *root);
void rotate_left(TreeNode *node);
void rotate_right(TreeNode *node);
TreeNode * Find_Succesor(TreeNode *node);
int max_height(TreeNode * a, TreeNode * b);
int get_balance(TreeNode *node);
TreeNode * delete_successor(TreeNode *root, int key);
TreeNode *rotateLeft_deletion(TreeNode *node);
TreeNode *rotateRight_deletion(TreeNode *node);

#endif //PA4_PA3_H
