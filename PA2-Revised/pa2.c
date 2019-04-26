#include "shell_array.h"
#include "shell_list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Still Need to do:
//-Check for empty files.
//-Do "Triangle" optimization 

int main(int argc, char const *argv[])
{
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

        if(input_size == 0 ){
            FILE *output_fptr = fopen(output_filename, "w");
            fclose(output_fptr);
            return EXIT_SUCCESS;
        }

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
        Node *head = List_Load_From_File(input_filename, &input_size);

        if(input_size == 0 ){
            FILE *output_fptr = fopen(output_filename, "w");
            fclose(output_fptr);
            return EXIT_SUCCESS;
        }


        if (head == NULL)
        {
            printf("File List Could Not Be Generated\n");
            return EXIT_FAILURE;
        }

        //Sort Linked List
        double n_comp = 0;
        head = List_Shellsort(head, &n_comp, input_size);

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

    return 0;
}
