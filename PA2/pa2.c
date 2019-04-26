#include "shell_array.h"
#include "shell_list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
// #include <time.h>

//Still Need to do:
//-Implement time.h to check runtime.
//-Check for empty files.
//-Do "Triangle" optimization 

int main(int argc, char const *argv[])
{
  //Checking for Execution Time
  // clock_t begin = clock();

  if (argc != 4)
  {
    printf("Wrong Arguments\n");
    return EXIT_FAILURE;
  }

  //Variables
  int input_size = 0;
  const char *option = argv[1];
  char *input_filename = (char *) argv[2];
  char *output_filename = (char *) argv[3];


  //Determine which set of functions to use.
  if (!strcmp(option, "-a"))
  {
    long *file_array = Array_Load_From_File(input_filename, &input_size);
    
    if (file_array == NULL)
    {
      printf("File Array Could Not Be Generated\n");
      return EXIT_FAILURE;
    }

    // //Checking if array is generated correctly
    // printf("Array from Input:\n");
    // for (int i = 0; i < input_size; ++i)
    // {
    //   printf("%ld\n", file_array[i]);
    // }

    //Sort Array
    double n_comp = 0;
    Array_Shellsort(file_array, input_size, &n_comp);

    //Number of Comparisons:
    printf("%le\n", n_comp);

    //Write Array to Output File
    int long_saved_output = Array_Save_To_File(output_filename, file_array, input_size);

    if (long_saved_output < input_size)
    {
      printf("Array_Save_To_File Incomplete.\n");
    }

    //Free 
    free(file_array);

  }
  else if(!strcmp(option, "-l"))
  {
    Node *head = List_Load_From_File(input_filename);

    if (head == NULL)
    {
      printf("File List Could Not Be Generated\n");
      return EXIT_FAILURE;
    }

    //Checking for Linked List
    // Node *temp = head;
    // while(temp!=NULL)
    // {
    //   printf("%ld\n",temp->value);
    //   temp=temp->next;
    // }
    // printf("\n");

    //Sort Linked List
    double n_comp = 0;

    head = List_Shellsort(head, &n_comp);

    //Checking Sorting
    // Node *temp_p = head;
    // printf("Out List after sorting:\n");
    // while(temp_p != NULL)
    // {
    //   printf("%ld\n", temp_p->value);
    //   temp_p = temp_p->next;
    // }


    //Write Array to Output File
    int long_saved_output = List_Save_To_File(output_filename, head);

    if (long_saved_output < input_size)
    {
      printf("Array_Save_To_File Incomplete.\n");
    }

    //Free Head linked List
    Node *temp1 = head;
    Node *temp2;
    while(temp1 != NULL)
    {
      temp2 = temp1->next;
      free(temp1);
      temp1 = temp2;
    }

    head = NULL; 

    //Number of Comparisons:
    printf("%le\n", n_comp);
  }
  else
  {
    printf("Incorrect -l/-a argument\n");
    return EXIT_FAILURE;
  }

  //Checking Execution Time
  // clock_t end = clock();
  // double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  // printf("Execution Time (Sec): %f\n", time_spent);


  return 0;
}
