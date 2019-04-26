//
// Created by Jose Luis Tejada on 2019-03-25.
//

#ifndef PA1_REVISED_HUFFMAN_H
#define PA1_REVISED_HUFFMAN_H

//Structures
typedef struct
{
    char value;
    long freq;
}CharFreq;

typedef struct TNode
{
    struct TNode* left;
    struct TNode* right;
    char value; // character
    long freq;  // frequency
}TreeNode;

typedef struct LNode
{
    struct LNode *next;
    TreeNode* treenode;
}ListNode;


//Function Declarations
CharFreq * count_characters(const char *filename_in, const char *filename_out, int * num_unique_chars);
TreeNode * generate_tree(CharFreq *char_arr, ListNode *list_head,int num_unique_chars);
void bubble_sort_char(CharFreq *char_arr, int num_unique_chars);
ListNode * CreateNode(char val, long freq, TreeNode *left, TreeNode *right);
TreeNode * CreateNode_t(char val, long freq, TreeNode *left, TreeNode *right);
ListNode * sort_insert_node(ListNode * head, ListNode *temp);
void generate_Huffman_Code(TreeNode * root, int bit_encoding[256], int index, FILE *fptr_tree, FILE *fptr_code);
void delete_tree(TreeNode *root);

#endif //PA1_REVISED_HUFFMAN_H
