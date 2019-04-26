#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"

int main(int argc, char const *argv[])
{
    //Check Correct Number of Input Arguments
    if(argc < 5)
    {
        printf("Not Enough Arguments \n");
        return EXIT_FAILURE;
    }

    //Read Text, write text to count file, and Binary Files to determine character weights.  
    int num_unique_chars = 0;
    CharFreq *char_freq_arr = NULL;
    char_freq_arr = count_characters(argv[1], argv[2], &num_unique_chars);

    if ((char_freq_arr == NULL) && (num_unique_chars != -1))
    {
        printf("Error\n");
        return EXIT_FAILURE;
    }
    else if(num_unique_chars == -1){
        return EXIT_SUCCESS;
    }


    //Generate Tree for Unique Items.
    ListNode *list_head = NULL;
    TreeNode *root = generate_tree(char_freq_arr, list_head, num_unique_chars);

    if(root == NULL){
        printf("Error generating tree");
        return  EXIT_FAILURE;
    }

    //Print Generate Huffman Code
    int bit_encoding[256] = {-1};
    int index = 0;
    //Generate Huffman code table and print
    FILE *fptr_tree = fopen(argv[3], "w");
    if(fptr_tree == NULL){
        printf("Could not open .tree file");
        return EXIT_FAILURE;
    }

    FILE *fptr_code = fopen(argv[4], "w");
    if(fptr_code == NULL){
        printf("Could not open .tree file");
        return EXIT_FAILURE;
    }

    generate_Huffman_Code(root, bit_encoding,index,fptr_tree,fptr_code);
    fclose(fptr_tree);
    fclose(fptr_code);
    delete_tree(root);

    return EXIT_SUCCESS;
}
