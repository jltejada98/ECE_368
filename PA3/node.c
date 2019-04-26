#include "pa3.h"


///////////////////////////////
/////Function Definitions//////
///////////////////////////////
int Read_Header(char *filename, double *r_source, double *r, double *c)
{
  FILE *file_ptr = fopen(filename, "r");
  if (file_ptr == NULL)
  {
    printf("Error Opening Input File (Read_Header)\n");
    return -1;
  }

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
  //Reading first three varia1bles
  fscanf(file_ptr, "%le %le %le", r_source, r, c);

  int num_nodes = num_newlines - 1;
  fclose(file_ptr);
  
  return(num_nodes);
}


TreeNode * Create_Postorder(char *filename, int num_nodes)
{
  FILE *fptr = fopen(filename, "r");
  
  if (fptr == NULL)
  {
    printf("Error Opening Input File (Create_Postorder)\n");
    return NULL;
  }

  //Reach First Port Traversal Node
  char char_read = 0;
  while(char_read != '\n')
  {
    char_read = fgetc(fptr);
  }
  
  //Variables
  double length_L = 0;
  double length_R = 0;
  int label = -1;
  double capacitance = 0;
  TreeNode *new_Node = NULL;
  TreeNode *temp_r = NULL;
  TreeNode *temp_l = NULL;
  Stack *stack_list = Create_Stack(num_nodes);

  // printf("Num: %d\n", num_nodes);

  //Add Nodes to stack and build tree.
  for (int i = 0; i < num_nodes; ++i)
  {
    //Read new character
    char first_char = fgetc(fptr);
    // printf("%c\n",first_char);
    if (first_char == '(') //Non-leaf Node
    {
      fscanf(fptr,"%le %le)\n", &length_L, &length_R);
      new_Node = Create_Middle_Node(length_L, length_R);
      temp_r = Pop(stack_list);
      temp_l = Pop(stack_list);
      new_Node->right = temp_r;
      new_Node->left = temp_l;
    }
    else //Leaf Node
    {
      fseek(fptr, -1L, SEEK_CUR);
      fscanf(fptr, "%d(%le)\n",&label, &capacitance);
      new_Node = Create_Leaf_Node(label, capacitance);
    }

    Push(stack_list, new_Node);
  }

  new_Node = Pop(stack_list);
  free(stack_list->array);
  free(stack_list);
  fclose(fptr);

  return new_Node;
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
  return;
}

TreeNode * Pop(Stack *input_stack)
{
  (input_stack->top)--;
  return input_stack->array[input_stack->top + 1];
}

///////////////////////////////
////////Helper Functions///////
///////////////////////////////
void printPreorder(TreeNode *node, char *filename)
{
  //Open preorder output file.
  FILE *file_ptr = fopen(filename, "w");
  if (file_ptr == NULL)
  {
    printf("Error Opening Output File (Preorder)\n");
    return;
  }
  printPreorder_Helper(node, file_ptr); 
  fclose(file_ptr);
  return;
}

void printPreorder_Helper(TreeNode* node, FILE *fptr) 
{ 
  if (node == NULL) 
  {
    return;
  }

  if (node->label == -1)
  {
    fprintf(fptr, "(%le %le)\n",node->length_l, node->length_r);
  }
  else
  {
    fprintf(fptr, "%d(%le)\n",node->label, node->cap);
  }

  printPreorder_Helper(node->left, fptr);  
  printPreorder_Helper(node->right, fptr);  
  return;
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
  return;
}
