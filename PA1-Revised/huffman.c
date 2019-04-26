//
// Created by Jose Luis Tejada on 2019-03-25.
//

//edit this file as required
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"

CharFreq * count_characters(const char *filename_in, const char *filename_out, int * num_unique_chars)
{
    //Open input File
    FILE *fptr = fopen (filename_in, "r");

    if (fptr == NULL)
    {
        printf("Error Opening Input File\n");
        return NULL;
    }

    fseek(fptr, 0, SEEK_END);
    long file_size = ftell(fptr);

    if(file_size == 0){
        FILE *fptr2 = fopen(filename_out, "w");
        fclose(fptr2);
        *num_unique_chars = -1;
        return NULL;
    }

    fseek(fptr, 0, SEEK_SET);

    long char_array[256] = {0};
    int one_character = 0;

    while(!feof(fptr))
    {
        one_character = fgetc(fptr);
        if (one_character != EOF)
        {
            char_array[one_character] += 1;
        }
    }

    //Open Output File
    FILE *fptr2 = fopen(filename_out, "w");

    if (fptr2 == NULL)
    {
        printf("Error Opening Output File\n");
        return NULL;
    }

    //Write to output file.
    fwrite(char_array, 8, 256, fptr2);

    //Find number of unique characters.
    for (int i = 0; i < 256; ++i)
    {
        if (char_array[i] > 0)
        {
            *num_unique_chars += 1;
        }
    }

    //Initialize Character Structure
    CharFreq *char_freq = NULL;
    char_freq = malloc(sizeof(CharFreq) * (*num_unique_chars));
    int char_freq_index = 0;

    for (int i = 0; i < (*num_unique_chars); ++i)
    {
        char_freq[i].value = 0;
        char_freq[i].freq = 0;
    }

    //Initialize
    for (int i = 0; i < 256; ++i)
    {
        if (char_array[i] > 0)
        {
            char_freq[char_freq_index].freq = char_array[i];
            char_freq[char_freq_index].value = i;
            ++char_freq_index;
        }
    }

    fclose(fptr);
    fclose(fptr2);
    return char_freq;
}

void bubble_sort_char(CharFreq *char_arr, int num_unique_chars)
{
    //Sort frequency Array by frequency
    CharFreq temp;
    for (int i = 0; i < (num_unique_chars - 1); ++i)
    {
        for (int j = 0; j < ((num_unique_chars - 1) - i); ++j)
        {
            if (char_arr[j].freq > char_arr[j+1].freq )
            {
                temp = char_arr[j];
                char_arr[j] = char_arr[j+1];
                char_arr[j+1] = temp;
            }
        }
    }

    //Sort within frequency by ascii value
    for (int i = 0; i < ((num_unique_chars) - 1); ++i)
    {
        for (int j = 0; j < (((num_unique_chars) - 1) - i); ++j)
        {
            if (char_arr[j].freq == char_arr[j+1].freq)
            {
                if (char_arr[j].value > char_arr[j+1].value)
                {
                    temp = char_arr[j];
                    char_arr[j] = char_arr[j+1];
                    char_arr[j+1] = temp;
                }
            }
        }
    }
}

TreeNode * CreateNode_t(char val, long freq, TreeNode *left, TreeNode *right)
{
    TreeNode *new_node_tree = NULL;
    new_node_tree = malloc(sizeof(TreeNode));

    if (new_node_tree == NULL)
    {
        return NULL;
    }

    new_node_tree->left = left;
    new_node_tree->right = right;
    new_node_tree->value = val;
    new_node_tree->freq = freq;

    return new_node_tree;
}

ListNode * CreateNode(char val, long freq, TreeNode *left, TreeNode *right)
{
    // Define a new variable of type Node
    // allocate memory for the new Node*
    ListNode *new_node = NULL;
    new_node = malloc(sizeof(ListNode));

    // check memory allocation fails
    if (new_node == NULL)
    {
        return NULL;
    }
    new_node->next = NULL;
    new_node->treenode = CreateNode_t(val, freq, left, right);

    return new_node;
}


TreeNode * generate_tree(CharFreq *char_arr, ListNode *list_head,int num_unique_chars)
{
    //Sort character array.
    bubble_sort_char(char_arr, num_unique_chars);

    //Setup first listnode

    list_head = malloc(sizeof(ListNode));
    if (list_head == NULL)
    {
        return NULL;
    }

    list_head->next = NULL;
    list_head->treenode = NULL;
    list_head->treenode = malloc(sizeof(TreeNode));
    if (list_head->treenode == NULL)
    {
        return NULL;
    }

    list_head->treenode->left = NULL;
    list_head->treenode->right = NULL;
    list_head->treenode->value = char_arr[0].value;
    list_head->treenode->freq = char_arr[0].freq;

    //Make Linked List
    ListNode *temp_node = list_head;

    for (int i = 1; i < num_unique_chars; ++i)
    {
        while((temp_node->next) != NULL) //Goes to End of Linked List (Should we reset head to )
        {
            temp_node = temp_node->next;
        }
        temp_node->next = CreateNode(char_arr[i].value, char_arr[i].freq, NULL, NULL);
    }

////    //Print Linked List
//    ListNode *temp_p =  list_head;
//    while(temp_p != NULL){
//        printf("%c\n", temp_p->treenode->value);
//        temp_p = temp_p->next;
//    }



    //Make Finalized tree.
    int numb_nodes_left = num_unique_chars;
    ListNode *temp_L = NULL;
    ListNode *temp_R = NULL;
    ListNode * merged_node = NULL;

    while(numb_nodes_left > 1)
    {
        temp_L = list_head;
        temp_R = list_head->next;
        list_head = list_head->next->next;
        merged_node = CreateNode(0,temp_L->treenode->freq + temp_R->treenode->freq, temp_L->treenode, temp_R->treenode);
        //Free merged nodes
        free(temp_L);
        free(temp_R);
        list_head = sort_insert_node(list_head, merged_node);
        //RE-order inserted node.
        --numb_nodes_left;
    }
    TreeNode *root = list_head->treenode;
    free(list_head);

    return root;
}

ListNode * sort_insert_node(ListNode * head, ListNode *temp){
    if(head == NULL){
        head = temp;
        return head;
    }

    if(head->treenode->freq < temp->treenode->freq){
        head->next = sort_insert_node(head->next, temp);
    }
    else if(head->treenode->freq == temp->treenode->freq){
        head->next = sort_insert_node(head->next, temp);
    }
    else{
        temp->next = head;
        return temp;
    }
    return head;
}

void generate_Huffman_Code(TreeNode * root, int bit_encoding[256], int index, FILE *fptr_tree, FILE *fptr_code){
    if(root == NULL){
        return;
    }

    if(root->left == NULL && root->right == NULL){ //Found a leaf node
        //Write to code file.
        fprintf(fptr_code,"%c:", root->value);
        for (int i = 0; i < index; ++i) {
            fprintf(fptr_code,"%d",bit_encoding[i]);
        }
        fprintf(fptr_code, "\n");
        //Write to tree file.
        fprintf(fptr_tree, "1%c", root->value);
    }
    else{ //Non-leaf node
        if(root->left != NULL){
            bit_encoding[index] = 0;
            fprintf(fptr_tree, "0");
            generate_Huffman_Code(root->left, bit_encoding,index + 1, fptr_tree, fptr_code);
        }
        if(root->right != NULL){
            bit_encoding[index] = 1;
            generate_Huffman_Code(root->right, bit_encoding,index + 1, fptr_tree, fptr_code);
        }
    }
}


void delete_tree(TreeNode *root){
    if(root == NULL){
        return;
    }
    delete_tree(root->left);
    delete_tree(root->right);
    free(root);
}
