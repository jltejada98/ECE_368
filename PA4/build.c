//
// Created by Jose Luis Tejada on 2019-03-07.
//

#include "pa4.h"

TreeNode *Build_Load_From_File(FILE *fptr, long *tree_size, int *op_flag){
    //Determination of input size
    fseek(fptr, 0, SEEK_END);
    long file_size = ftell(fptr);
    long input_size = (file_size / (sizeof(int) + sizeof(char)));

    if(input_size == 0){ //Empty File --> Create new file anyways thats empty
        *op_flag = 0;
        return  NULL;
    }

    //Read file
    fseek(fptr, 0, SEEK_SET);
    int temp_val = 0;
    char temp_op = 0;
    TreeNode *root = NULL;
    //Checking Variables
    int check_read_val = 0;
    int check_read_op = 0;
    long num_insertions = 0;


    for (long ind = 0; ind < input_size; ++ind) {
        check_read_val = fread(&temp_val, sizeof(int), 1, fptr);
        check_read_op = fread(&temp_op, sizeof(char), 1, fptr);

        //Checking correct input file format.
        if((check_read_val != 1) && (check_read_op != 1)){
            fclose(fptr);
            *op_flag = 0;
            return root;
        }

        //Do Appropriate Operation.
        if(temp_op == 'i'){ //Insert Node
            root = insert_node(root, temp_val, tree_size);
            ++num_insertions;

            //Check for correctly read size
            if(*tree_size != num_insertions){
                fclose(fptr);
                *op_flag = 0;
                return root;
            }
        }
        else if (temp_op == 'd'){ //Delete Node
            // Consider same method as insertion function but with recursive implementation.
            root = delete_node(root,temp_val, tree_size);

        }
        else{
            //printf("Error, Incorrect d/i option for tree");
            *op_flag = 0;
            fclose(fptr);
            return NULL;
        }
    }

    //If everything goes well print 1
    *op_flag = 1;

    return root;
}


void Build_Write_To_File(TreeNode *root, FILE *fptr){
    if(root == NULL){
        return;
    }

    //Write node value
    fwrite(&root->value, sizeof(int), 1, fptr);

    //Write char code
    char code = 0X00000000;
    if(root->right != NULL){
        code = code | (char)(1 << 0);
    }
    if(root->left != NULL){
        code = code | (char)(1 << 1);
    }
    //Write char value.
    fwrite(&code, sizeof(char), 1,fptr);
    //Printout Values
//    printf("%d %c\n", root->value, code+48);
    //Proceed with Traversal
    Build_Write_To_File(root->left, fptr);
    Build_Write_To_File(root->right, fptr);
}
