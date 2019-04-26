#include "shell_list.h"
#include "sequence.h"
#include <stdio.h>
#include <stdlib.h>

//Structure Declarations
typedef struct List { 
  Node *node;
  struct List *next; 
} List;


//Helper Function Declarations
Node * Helper_CreateNode(long);
List * Helper_CreateList(Node *);
List * Helper_Split_List(int, int, Node *);
Node * Helper_Insertion_Sort(Node *, double *);
Node * Helper_Merge_List(int, int, List *);
void Helper_Delete_List(List *);

Node *List_Load_From_File(char *filename)
{
  FILE *file_ptr = fopen(filename, "r");

  if (file_ptr == NULL)
  {
    printf("Error Opening Input File (Node)\n");
    return NULL;
  }

  //Determination of size of input file 
  fseek(file_ptr, 0, SEEK_END);
  long file_size = ftell(file_ptr);
  int size = (file_size / sizeof(long));

  //If file empty do we allocate memory anyways?
  if (size == 0)
  {
    return NULL;
  }

  //Reading file one long at a time.
  fseek(file_ptr, 0, SEEK_SET);

  //Creation of Head (Reading First Element)
  long temp_value = 0;
  fread(&temp_value, sizeof(long),1, file_ptr);
  Node *head = Helper_CreateNode(temp_value);

  //Creation of Subsequent Nodes.
  Node *temp = head;

  for (int i = 1; i < size; ++i)
  {
    while((temp->next) != NULL)
    {
      temp = temp->next;
    }
    fread(&temp_value, sizeof(long),1, file_ptr);
    temp->next = Helper_CreateNode(temp_value);
  }

  fclose(file_ptr);

  return head;
}

int List_Save_To_File(char *filename, Node *list)
{
  FILE *file_ptr = fopen(filename, "w");

  if (file_ptr == NULL)
  {
    printf("Error Opening Output File\n");
    return 0;
  }

  Node *temp = list;
  int num_written = 0;
  long write = 0;
  while(temp != NULL)
  {
    write = temp->value;
    num_written += fwrite(&write, sizeof(long), 1, file_ptr);
    temp = temp->next;
  }

  fclose(file_ptr);

  return num_written;
}

Node *List_Shellsort(Node *list, double *n_comp)
{
  //Determination of Length of Linked List
  int size = 0;
  Node *temp = list;
  while(temp!=NULL)
  {
    ++size;
    temp = temp->next;
  }

  //Length of Linked List
  // printf("Size: %d\n",size);

  //Sequence Generation
  int seq_size = 0;
  long *sequence = Generate_2p3q_Seq(size, &seq_size);

  if (sequence == NULL)
  {
    printf("Error Generating Sequence\n"); 
    return NULL;
  }

  //Checking Sequence
  // printf("Sequence:\n");
  // for (int i = 0; i < seq_size; ++i)
  // {
  //   printf("%ld\n", sequence[i]);
  // }
  

  //Shell Sort Implementation
  long current_k = 0;
  List *temp_list = NULL;

  for (int k = (seq_size - 1); k > 0; --k) //for each k (in descending order)
  {
    current_k = sequence[k];
    List *k_sublist = Helper_Split_List(current_k, size, list); //Split Original Linked List into k Linked Lists
    temp_list = k_sublist;
    //Sort Each Sublist
    while(temp_list != NULL)
    {
      temp_list->node = Helper_Insertion_Sort(temp_list->node, n_comp);
      temp_list = temp_list->next;
    }

    //Check k Sorting
    // printf("%ld Sorted.\n", current_k);
    // List *temp_l = k_sublist;
    // Node *temp_n = temp_l->node;
    // int i = 0;
    // while(temp_l != NULL)
    // {
    //   printf("Sublist :%d : ",i);
    //   while(temp_n != NULL)
    //   {
    //     printf("%ld, ",temp_n->value);
    //     temp_n = temp_n->next;
    //   }
    //   printf("\n");
    //   temp_l = temp_l->next;
    //   temp_n = temp_l->node;
    //   ++i;
    // }
    
    //Merge all Sublists
    list = Helper_Merge_List(current_k, size, k_sublist);

    // if (k == 1)
    // {
    //   //Checking Sorting
    //   Node *temp_p = list;
    //   printf("List after sorting:\n");
    //   for (int ind = 0; ind < size; ++ind)
    //   {
    //     printf("%ld\n", temp_p->value);
    //     temp_p = temp_p->next;
    //   }
    // }
  }

  //Perform k = 1 Insertion sort
  list = Helper_Insertion_Sort(list, n_comp);

  free(sequence);

  return list;
}

///////////////////////////////
//Helper Function Definitions//
///////////////////////////////

Node * Helper_CreateNode(long value)
{
  Node *new_Node = malloc(sizeof(Node));

  if (new_Node == NULL)
  {
    printf("New Node Allocation Failure.\n");
    return NULL;
  }

  new_Node->value = value;
  new_Node->next = NULL;

  return new_Node;
}

List * Helper_CreateList(Node *node)
{
  List * new_List = malloc(sizeof(List));

  if (new_List == NULL)
  {
    printf("New List Allocation Failure.\n");
    return NULL;
  }
  // printf("Node to add : %ld\n",node->value);
  node->next = NULL;
  new_List->node = node;
  new_List->next = NULL;

  return new_List;
}

List * Helper_Split_List(int k, int size, Node *head)
{
  //Creation of First ListNode in Sub-List
  Node *temp_node = head->next;
  List *list_head = Helper_CreateList(head);
  List *temp_list = list_head;

  //Traversal of K nodes (Only To Generate First Row of List)
  for (int k_index = 1; k_index < k; ++k_index)
  {
    while((temp_list->next) != NULL) //Adding Elements at End of List.
    {
      temp_list = temp_list->next;
    }
    head = temp_node->next;
    temp_list->next = Helper_CreateList(temp_node);
    temp_node = head; //Next Node Traversal
  }

  //Checking for K Sublists
  // List *temp_list_print = list_head;
  // for (int i = 0; i < k; ++i)
  // {
  //   printf("Sublist %i : %ld\n",i, temp_list_print->node->value);
  //   temp_list_print = temp_list_print->next;
  // }

  // printf("Head Value:%ld\n", head->value);
  
  //Correct up to here

  //Addition of Subsequent Nodes to Each SubList
  temp_node = head;
  temp_list = list_head;

  // printf("List val: %ld\n", list_head->node->value);

  Node *temp_node_list = temp_list->node; //First Node of List.
  int k_index = 0;
  int node_index = k;
  while(node_index < size)
  {
    while((k_index < k) && (node_index < size)) //Traverse Each K SubList
    {
      //Reach Last Node on each Sublist to add new element.
      while((temp_node_list != NULL) && (temp_node_list->next != NULL))
      {
        temp_node_list = temp_node_list->next;
      }
      //Adding New Node
      temp_node_list->next = temp_node; //Add New Node
      head = temp_node->next; //Set new head.
      temp_node->next = NULL; //Unlink Node

      //Increment Next Node to be added
      temp_node = head;
      temp_list = temp_list->next;
      if (temp_list != NULL)
      {
        temp_node_list = temp_list->node;
      }

      ++node_index;
      ++k_index;
      // printf("%d\n", node_index);
    }
    //Start back at begging of List
    k_index = 0;
    temp_list = list_head;
    temp_node_list = temp_list->node; //First Node of List.
  }

  //Print K Sub-lists
  // printf("Unsorted.\n");
  // List *temp_l = list_head;
  // Node *temp_n = temp_l->node;
  // int i = 0;
  // while(temp_l != NULL)
  // {
  //   printf("Sublist :%d : ",i);
  //   while(temp_n != NULL)
  //   {
  //     printf("%ld, ",temp_n->value);
  //     temp_n = temp_n->next;
  //   }
  //   printf("\n");
  //   temp_l = temp_l->next;
  //   temp_n = temp_l->node;
  //   ++i;
  // }

  return list_head;
}

Node * Helper_Insertion_Sort(Node* head, double *n_comp)
{
  Node *temp_1 = head; 
  Node *temp_2 = NULL;
  Node *temp_3 = NULL;

  head = NULL;

  while(temp_1 != NULL)
  {
    temp_3 = temp_1;
    temp_1 = temp_1->next;
    if (head != NULL)
    { 
      if(temp_3->value > head->value)
      {
        temp_2 = head;
        ++(*n_comp);
        while ((temp_2->next != NULL) && (temp_3->value > temp_2->next->value))
        {
          temp_2 = temp_2->next;
          ++(*n_comp);
        }
        temp_3->next = temp_2->next;
        temp_2->next = temp_3;
      }
      else
      {
        temp_3->next = head;
        head = temp_3;
      }
    }
    else
    {
      temp_3->next = NULL;
      head = temp_3;
    }
  }

  return head;
}

Node * Helper_Merge_List(int k, int size, List * head)
{
  //List/Nodes in K sublists
  List * temp_list = head;
  Node * temp_list_node = temp_list->node;
  
  //Creation of first node in merged list.
  Node * merged_head = temp_list_node;
  Node * merged_temp = merged_head;
  
  //Progression of List/Node
  temp_list->node = temp_list_node->next;
  merged_temp->next = NULL; //Unlinking Node
  temp_list = temp_list->next; //Moving to Next item in list.  
  // printf("Merged Head: %ld\n",merged_head->value);

  int n_index = 1;
  int k_index = 1;

  while(n_index < size) //Do for all elements
  {
    while((k_index < k) && (n_index < size)) //Iterate through k sublists
    {
      //Select Node to Add to Merged List.
      temp_list_node = temp_list->node;
      merged_temp->next = temp_list_node;
      temp_list->node = temp_list_node->next;

      //Increment merged temp
      merged_temp = merged_temp->next;
      merged_temp->next = NULL; //Unlinking Node
      temp_list = temp_list->next; //Moving to Next item in list.
      ++n_index;
      ++k_index;
    }
    //Start Back at begging of list.
    k_index = 0;
    temp_list = head;
    temp_list_node = temp_list->node;
  }

  //Print Merged List
  // Node *temp_print = merged_head;
  // printf("Merged List\n");
  // while(temp_print != NULL)
  // {
  //   printf("%ld\n", temp_print->value);
  //   temp_print = temp_print->next;
  // }

  //Free Linked List.
  Helper_Delete_List(head);

  return merged_head;
}

void Helper_Delete_List(List * head)
{
  List *temp1 = head;
  List *temp2;
  while(temp1 != NULL)
  {
    temp2 = temp1->next;
    free(temp1);
    temp1 = temp2;
  }

  return;
}
