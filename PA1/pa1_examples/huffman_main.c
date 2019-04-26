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
  long num_unique_chars = 0;
  CharFreq *char_freq_arr = NULL;
  char_freq_arr = count_characters(argv[1], argv[2], &num_unique_chars);

  if (char_freq_arr == NULL)
  {
     printf("Error\n");
  }

  if (num_unique_chars == 0)
  {
    printf("Nothing Read\n");
    return EXIT_FAILURE;
  }

  //Generate Tree for Unique Items.
  ListNode *list_head = NULL;
  //generate_tree(char_freq_arr, list_head, &num_unique_chars);



  return EXIT_SUCCESS;
}
