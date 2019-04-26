//
// Created by Jose Luis Tejada on 2019-03-12.
//
#include "pa4.h"

TreeNode *Build_Tree(TreeNode *root, FILE *fptr, long ind, long size, int *read_successful){
    //End condition, reached end of file
    if(ind >= size){
        *read_successful = 0; //Read File Unsuccessfully as last node is expected to have no children
        return root;
    }

    //Reading from file, Checking Variables
    int temp_val = 0;
    char temp_char = 0;
    int check_read_val = fread(&temp_val, sizeof(int), 1, fptr);
    int check_read_op = fread(&temp_char, sizeof(char), 1, fptr);

    //Checking correct input file format.
    if((check_read_val != 1) && (check_read_op != 1)){ //Incorrect Format.
        return root;
    }


    //Determination of node configuration to build
    if(temp_char == 3){ //Right/Left Children
        root = create_node(temp_val);
        root->left = Build_Tree(root->left, fptr, ind + 1, size, read_successful);
        root->right = Build_Tree(root->right, fptr, ind + 1, size, read_successful);
    }
    else if(temp_char == 2){ //Left Child only
        root = create_node(temp_val);
        root->left = Build_Tree(root->left, fptr, ind + 1, size, read_successful);
    }
    else if(temp_char == 1){ //Right Child only
        root = create_node(temp_val);
        root->right = Build_Tree(root->right, fptr, ind + 1, size, read_successful);
    }
    else if(temp_char == 0){  //No Left/Right Children, last node of tree.
        root = create_node(temp_val);
        *read_successful = 1;
    }
    else{ //Incorrect Format.
        *read_successful = 0;
        return root;
    }

    return root;
}

int Evaluate_BST(TreeNode *root, int lower, int upper){ //Does not function for invalidtree2.b, returns 0 instead of 1
    //End condition
    if(root == NULL){
        return 1;
    }

    int valid_BST = (root->value < upper) && (root->value >= lower) && Evaluate_BST(root->left, lower, root->value) &&
            Evaluate_BST(root->right, root->value, upper);

    return valid_BST;
}

int Evaluate_Balance(TreeNode *root){
    if(root == NULL){
        return  1;
    }

    int valid_Balanced = Evaluate_Balance(root->left) && Evaluate_Balance(root->right);

    //Determine Children
    if((root->left == NULL) && (root->right == NULL)){ //Leaf Node
        return 1; //Node is Balanced
    }
    else if((root->left != NULL) && (root->right == NULL) ){ //Only Left Child
        root->balance = root->left->balance + 1;
    }
    else if((root->right != NULL) && (root->left == NULL)){ //Right Child
        root->balance = root->right->balance - 1;
    }
    else{ //Two Children
        root->balance = root->left->balance - root->right->balance; //Check if correct
    }

    if(root->balance <= -2 || root->balance >= 2){
        return 0;
    }

    return valid_Balanced;
}
