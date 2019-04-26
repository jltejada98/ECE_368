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

int Read_Header(char *filename, double *r_source, double *r, double *c);
TreeNode * Create_Postorder(char *filename, int newlines);
TreeNode * Create_Leaf_Node(int label, double capacitance);
TreeNode * Create_Middle_Node(double length_L, double length_R);
Stack * Create_Stack(int size);
void Push (Stack *input_stack, TreeNode *new_item);
TreeNode * Pop(Stack *input_stack);
void printPreorder(TreeNode *node, char *filename);
void printPreorder_Helper(TreeNode* node, FILE *fptr);
void Free_Tree_Helper(TreeNode *root_node);
void Determine_CR(TreeNode *node_i,double WL, double WC, double WR, double r_path);
void Determine_CD(TreeNode * node);
void Determine_Time_Delay_Helper(TreeNode * node, double time, char *filename);
