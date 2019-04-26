//edit this file as required
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"

CharFreq * count_characters(const char *filename_in, const char *filename_out, long * num_unique_chars)
{
  //Open input File
  FILE *fptr = fopen (filename_in, "r");
 
  if (fptr == NULL)
  {
    printf("Error Opening Input File\n");
    return NULL;
  }

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

void bubble_sort_char(CharFreq *char_arr,long * num_unique_chars)
{
  //Sort frequency Array by frequency
  CharFreq temp;
  for (int i = 0; i < ((*num_unique_chars) - 1); ++i)
  {
    for (int j = 0; j < (((*num_unique_chars) - 1) - i); ++j)
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
  for (int i = 0; i < ((*num_unique_chars) - 1); ++i)
  {
    for (int j = 0; j < (((*num_unique_chars) - 1) - i); ++j)
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

  if (new_node_tree)
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


void generate_tree(CharFreq *char_arr, ListNode *list_head,long * num_unique_chars)
{
  //Sort character array.
  bubble_sort_char(char_arr, num_unique_chars);
  
  for (int i = 0; i < *num_unique_chars; ++i)
  {
    printf("%c : %ld\n", char_arr[i].value,char_arr[i].freq);
  }

  //Setup first listnode

  list_head = malloc(sizeof(ListNode));
  if (list_head == NULL)
  {
    return;
  }

  list_head->next = NULL;
  list_head->treenode = NULL;
  list_head->treenode = malloc(sizeof(TreeNode));
  if (list_head == NULL)
  {
    return;
  }

  list_head->treenode->left = NULL;
  list_head->treenode->right = NULL;
  list_head->treenode->value = char_arr[0].value;
  list_head->treenode->freq = char_arr[0].freq;

  //Make Linked List
  ListNode *temp_node = list_head;

  for (int i = 1; i < *num_unique_chars; ++i)
  {
    while((temp_node->next) != NULL) //Goes to End of Linked List (Should we reset head to )
    {
      temp_node = temp_node->next;
    }
    temp_node->next = CreateNode(char_arr[i].value, char_arr[i].freq, NULL, NULL);
  }

  int numb_nodes_left = num_unique_chars;
  temp_node = list_head;
  while(numb_nodes_left > 1)
  {
    long sum_frequency = temp_node->treenode->freq + temp_node->next->treenode->freq;
    if ((temp_node->treenode->left == NULL) && (temp_node->treenode->right == NULL))
    {
      /* code */
    }


  }


  return;
}
