//
// Created by Jose Luis Tejada on 2019-03-10.
//
#include "pa4.h"

int max_height(TreeNode * a, TreeNode * b){
    int max = 0;
    //Determine Heights
    int height_a = -1;
    int height_b = -1;

    if(a != NULL){
        height_a = a->height;
    }
    if(b != NULL){
        height_b = b->height;
    }

    //Determine maximum
    if(height_a > height_b){
        max = height_a;
    }
    else {
        max = height_b;
    }
    return  max;
}

int get_balance(TreeNode *node){
    if(node == NULL){
        return -1;
    }

    int height_left = -1;
    int height_right = -1;

    if(node->left != NULL){
        height_left = node->left->height;
    }

    if(node->right != NULL){
        height_right = node->right->height;
    }

    return height_left - height_right;
}


TreeNode *create_node(int value){
    TreeNode *temp = malloc(sizeof(TreeNode));

    if(temp == NULL){
//        printf("New Node Allocation Unsuccessful");
        return  NULL;
    }

    temp->value = value;
    temp->left = NULL;
    temp->right = NULL;
    temp->balance = 0;
    temp->height = 0;
    temp->delete = 0;

    return temp;
}

void free_tree(TreeNode *root){
    if(root == NULL){
        return;
    }

    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

void rotate_left(TreeNode *node){
    TreeNode *new_root = node->right;
    TreeNode *temp = new_root->left;
    new_root->left = node;
    node->right = temp;

    //Update Heights
    node->height = max_height(node->left, node->right) + 1;
    new_root->height = max_height(new_root->left, new_root->right) + 1;
}

void rotate_right(TreeNode *node){
    TreeNode *new_root = node->left;
    TreeNode *temp = new_root->right;
    new_root->right = node;
    node->left = temp;

    //Update Heights
    node->height = max_height(node->left, node->right) + 1;
    new_root->height = max_height(new_root->left, new_root->right) + 1;

}

TreeNode *insert_node(TreeNode *root, int key, long *tree_size){
    //Variables
    TreeNode * curr = root;
    TreeNode * curr_ya = root;
    TreeNode * parent = NULL;
    TreeNode * parent_ya = NULL;
    TreeNode * temp = NULL;

    while(curr != NULL){//Traverse tree until reached desired position. (Iterative implementation)
        if(key <= (curr->value)){ //If equal values, traverse left.
            temp = curr->left;
        }
        else{
            temp = curr->right;
        }
        //Balance checking to determine possible nodes to rotate for parent and child of lookup node.
        if((temp != NULL) && (temp->balance != 0)) {
            parent_ya = curr;
            curr_ya = temp;
        }

        parent = curr;
        curr = temp;
    }

    //Create Node
    temp = create_node(key);

    //Check for unsuccessful memory allocation.
    if(temp == NULL){
        return  root;
    }
    else{
        *tree_size += 1;
    }

    if(parent == NULL){ //Create Root
        root = temp;
        return  root;
    }
    else{ //Create non-root node.
        if(key <= (parent->value)){
            parent->left = temp;
        }
        else{
            parent->right = temp;
        }
    }

    //Update Balance & Heights
    curr = curr_ya;
    while (curr != temp){
        if(key <= (curr->value)){
            curr->balance += 1;
            curr->height += 1;
            curr = curr->left;
        }
        else{
            curr->balance -= 1;
            curr->height += 1;
            curr = curr->right;
        }
    }

    //Check if rotation is required to keep balance
    if((curr_ya->balance < 2) && (curr_ya->balance > -2)){ //Balance -1,0,+1
        //Consider updating heights to non rotating nodes.
        TreeNode *temp_up = root;
        while(temp_up != temp){ //Traverse Tree to update heights
            if(key <= (temp_up->value)){ //If equal values, traverse left.
                //Update height
                temp_up->height = max_height(temp_up->right, temp_up->left) + 1;
                temp_up = temp_up->left;
            }
            else{ //Traverse right.
                //Update height
                temp_up->height = max_height(temp_up->right, temp_up->left) + 1;
                temp_up = temp_up->right;
            }
        }

        root->height = max_height(root->left, root->right) + 1;

        return  root;
    }

    //Unbalanced Node
    //Determine Child into which temp is inserted
    TreeNode *child = NULL;
    if(key <= curr_ya->value){
        child = curr_ya->left;
    }
    else{
        child = curr_ya->right;
    }

    //The Subtree located at ya requires balancing
    //Cases for balancing (Consider using if statements instead of elseif chain,
    //As shown by the textbook).
    if((curr_ya->balance == 2) && (child->balance == 1)){
        curr = child;
        rotate_right(curr_ya);
        curr_ya->balance = 0;
        child->balance = 0;
    }
    else if((curr_ya->balance == -2) && (child->balance == -1)){
        curr = child;
        rotate_left(curr_ya);
        curr_ya->balance = 0;
        child->balance = 0;
    }
    else if((curr_ya->balance == 2) && (child->balance == -1)){
        curr = child->right;
        rotate_left(child);
        curr_ya->left = curr;
        rotate_right(curr_ya);

        //Cases to Balance non-selected nodes.
        if(curr->balance == 0){
            curr_ya->balance = 0;
            child->balance = 0;
        }
        else{
            if(curr->balance == 1){
                curr_ya->balance = -1;
                child->balance = 0;
            }
            else{
                curr_ya->balance = 0;
                child->balance = 1;
            }
            curr->balance = 0;
        }
    }
    else if((curr_ya->balance == -2) && (child->balance == 1)){
        curr = child->left;
        rotate_right(child);
        curr_ya->right = curr;
        rotate_left(curr_ya);

        if(curr->balance == 0){
            curr_ya->balance = 0;
            child->balance = 0;
        }
        else{
            if(curr->balance == -1){
                curr_ya->balance = 1; //Changed from 0 to 1
                child->balance = 0;
            }
            else{
                curr_ya->balance = 0;
                child->balance = -1;
            }
            curr->balance = 0;
        }
    }

    //Determine which combination of nodes to return
    if(parent_ya == NULL){
        root = curr;
    }
    else{
        if(key <= parent_ya->value){
            parent_ya->left = curr;
        }
        else{
            parent_ya->right = curr;
        }
    }
    //Consider updating height of root
    root->height = max_height(root->left, root->right) + 1;


    return  root;
}

TreeNode * Find_Succesor(TreeNode *node){
    TreeNode *temp = node->left;

    while(temp->right != NULL){ //Finds immediate predecessor in a in-order traversal
        temp = temp->right;
    }

    return temp;
}

TreeNode *delete_node(TreeNode *root, int key, long *tree_size){ //Uses only balances to determine if rotations needed.
    //Base Case
    if(root == NULL){
        return root; //No node to delete
    }

    //Traversal of tree to search node.
    if(key < root->value){
        root->left = delete_node(root->left,key, tree_size);
    }
    else if(key > root->value){
        root->right = delete_node(root->right, key, tree_size);
    }
    else //Found key to delete.
    {
        if(root->left == NULL && root->right == NULL){//Case 1: No children
            free(root);
            --tree_size;
            return NULL;
        }
        else if(root->left != NULL && root->right == NULL){ //Case 2: Left Child
            TreeNode *temp =  root->left;
            free(root);
            --tree_size;
            return temp;
        }
        else if (root->right != NULL && root->left == NULL){ //Case 3: Right Child
            TreeNode *temp = root->right;
            free(root);
            --tree_size;
            return temp;
        }
        else{ //Case 4: Two Children
            // Determine immediate successor in in-order traversal.
            TreeNode *successor = Find_Succesor(root);
            //Pass data
            root->value = successor->value;
            successor->value = key;
            successor->delete = 1;
            //Delete in-order successor.
            root->left = delete_successor(root->left, key);
            --tree_size;
        }
    }

    //Update heights
    root->height = max_height(root->left, root->right) + 1;
    int balance = get_balance(root);
    root->balance = balance;

    if(balance > 1 && get_balance(root->left) >= 0){
        return rotateRight_deletion(root);
    }

    if (balance > 1 && get_balance(root->left) < 0)
    {
        root->left = rotateLeft_deletion(root->left);
        return rotateRight_deletion(root);
    }

    if (balance < -1 && get_balance(root->right) <= 0) {
        return rotateLeft_deletion(root);
    }

    if (balance < -1 && get_balance(root->right) > 0)
    {
        root->right = rotateRight_deletion(root->right);
        return rotateLeft_deletion(root);
    }

    return root;
}


TreeNode * delete_successor(TreeNode *root, int key){
//    if(root == NULL){
//        return  root;
//    }

    if((root->value == key) && (root->delete == 1)){ //Found node to delete
        if(root->left == NULL && root->right == NULL){//Case 1: No children
            free(root);
            return NULL;
        }
        else if(root->left != NULL && root->right == NULL){ //Case 2: Left Child
            TreeNode *temp =  root->left;
            free(root);
            return temp;
        }
    }
    else{
        //Otherwise traverse tree.
        root->right = delete_successor(root->right, key);
    }

    //Update heights
    root->height = max_height(root->left, root->right) + 1;
    int balance = get_balance(root);
    root->balance = balance;

    //Consider update balances after rotation.
    if(balance > 1 && get_balance(root->left) >= 0){
        return rotateRight_deletion(root);
    }

    if (balance > 1 && get_balance(root->left) < 0)
    {
        root->left = rotateLeft_deletion(root->left);
        return rotateRight_deletion(root);
    }

    if (balance < -1 && get_balance(root->right) <= 0) {
        return rotateLeft_deletion(root);
    }

    if (balance < -1 && get_balance(root->right) > 0)
    {
        root->right = rotateRight_deletion(root->right);
        return rotateLeft_deletion(root);
    }

    return root;
}

//Second Set of rotation functions
TreeNode *rotateRight_deletion(TreeNode *node){
    TreeNode *new_root = node->left;
    TreeNode *temp = new_root->right;
    new_root->right = node;
    node->left = temp;

    //Update Heights
    node->height = max_height(node->left, node->right) + 1;
    new_root->height = max_height(new_root->left, new_root->right) + 1;

    return new_root;
}

TreeNode *rotateLeft_deletion(TreeNode *node){
    TreeNode *new_root = node->right;
    TreeNode *temp = new_root->left;
    new_root->left = node;
    node->right = temp;

    //Update Heights
    node->height = max_height(node->left, node->right) + 1;
    new_root->height = max_height(new_root->left, new_root->right) + 1;

    return new_root;
}
