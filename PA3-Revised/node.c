//
// Created by Jose Luis Tejada on 2019-03-25.
//

#include "pa3.h"


///////////////////////////////
/////Function Definitions//////
///////////////////////////////
int Read_Header(FILE *file_ptr, double *r_source, double *r, double *c)
{
    //Determine Number of Newlines in txt file
    int num_newlines = 0;
    char char_read = 0;
    while(!feof(file_ptr))
    {
        char_read = fgetc(file_ptr);
        if (char_read == '\n')
        {
            ++num_newlines;
        }
    }

    if (num_newlines == 0) //Empty File
    {
        fclose(file_ptr);
        return 0;
    }

    fseek(file_ptr,0,SEEK_SET);
    //Reading first three variables
    int check_read_values = fscanf(file_ptr, "%le %le %le", r_source, r, c);
    //Check Read Values
    if(check_read_values == 0){
        return  -1;
    }

    long num_nodes = num_newlines - 1;

    return(num_nodes);
}


TreeNode * Create_Postorder(FILE *fptr, int num_nodes)
{
    //Variables
    double length_L = 0;
    double length_R = 0;
    int label = -1;
    double capacitance = 0;
    TreeNode *new_Node = NULL;
    TreeNode *temp_r = NULL;
    TreeNode *temp_l = NULL;
    Stack *stack_list = Create_Stack(num_nodes);
    int check_read_value = 0;

    // printf("Num: %d\n", num_nodes);

    //Add Nodes to stack and build tree.
    for (int i = 0; i < num_nodes; ++i)
    {
        //Read new character
        char first_char = fgetc(fptr);
        // printf("%c\n",first_char);
        if (first_char == '(') //Non-leaf Node
        {
            check_read_value = fscanf(fptr,"%le %le)\n", &length_L, &length_R);
            if(check_read_value == 0){
                Free_Tree_Helper(new_Node);
                return  NULL;
            }
            new_Node = Create_Middle_Node(length_L, length_R);
            temp_r = Pop(stack_list);
            temp_l = Pop(stack_list);
            new_Node->right = temp_r;
            new_Node->left = temp_l;
        }
        else //Leaf Node
        {
            fseek(fptr, -1L, SEEK_CUR);
            check_read_value = fscanf(fptr, "%d(%le)\n",&label, &capacitance);
            if(check_read_value == 0){
                Free_Tree_Helper(new_Node);
                return  NULL;
            }
            new_Node = Create_Leaf_Node(label, capacitance);
        }

        Push(stack_list, new_Node);
    }

    TreeNode *root = Pop(stack_list);
    free(stack_list->array);
    free(stack_list);
    fclose(fptr);

    return root;
}


TreeNode * Create_Leaf_Node(int label, double capacitance)
{
    TreeNode *new_Node = malloc(sizeof(TreeNode));

    if (new_Node == NULL)
    {
        printf("New Tree Node Allocation Failure.\n");
        return NULL;
    }

    new_Node->label = label;
    new_Node->cap = capacitance;
    new_Node->length_l = 0;
    new_Node->length_r = 0;
    new_Node->left = NULL;
    new_Node->right = NULL;
    new_Node->c_down = 0;
    new_Node->r_path = 0;

    return new_Node;
}

TreeNode * Create_Middle_Node(double length_L, double length_R)
{
    TreeNode *new_Node = malloc(sizeof(TreeNode));

    if (new_Node == NULL)
    {
        printf("New Tree Node Allocation Failure.\n");
        return NULL;
    }

    new_Node->label = -1;
    new_Node->cap = 0;
    new_Node->length_l = length_L;
    new_Node->length_r = length_R;
    new_Node->left = NULL;
    new_Node->right = NULL;
    new_Node->c_down = 0;
    new_Node->r_path = 0;

    return new_Node;
}


//Stack Functions
Stack * Create_Stack(int size)
{
    Stack *new_stack = malloc(sizeof(Stack));
    new_stack->capacity = size;
    new_stack->top = -1;
    new_stack->array = malloc(sizeof(TreeNode) * size);
    return new_stack;
}


void Push(Stack *input_stack, TreeNode *new_item)
{
    (input_stack->top)++;
    input_stack->array[input_stack->top] = new_item;
}

TreeNode * Pop(Stack *input_stack)
{
    (input_stack->top)--;
    return input_stack->array[input_stack->top + 1];
}

///////////////////////////////
////////Helper Functions///////
///////////////////////////////

void printPreorder(TreeNode* node, FILE *fptr, int num_nodes)
{
    if(node == NULL){
        return;
    }

    Stack *stack_list = Create_Stack(num_nodes);
    int check_read_value = 0;
    Push(stack_list,node);

    TreeNode *temp_node;
    while(stack_list->top != -1){
        temp_node = Pop(stack_list);
        //Printing
        if (temp_node->label == -1)
        {
            fprintf(fptr, "(%le %le)\n",node->length_l, node->length_r);
        }
        else
        {
            fprintf(fptr, "%d(%le)\n",node->label, node->cap);
        }
        //Pushing new nodes to stack.
        if(temp_node->right != NULL){
            Push(stack_list, temp_node->right);
        }

        if(temp_node->left != NULL){
            Push(stack_list, temp_node->left);
        }
    }

    free(stack_list->array);
    free(stack_list);
    fclose(fptr);
}

void Free_Tree_Helper(TreeNode *root_node)
{
    if (root_node == NULL)
    {
        return;
    }

    Free_Tree_Helper(root_node->left);
    Free_Tree_Helper(root_node->right);
    free(root_node);
}
