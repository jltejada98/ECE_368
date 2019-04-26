#include "pa3.h"

///////////////////////////////
////////Main Functions////////
///////////////////////////////

int main(int argc, char const *argv[])
{
    if (argc != 4)
    {
        printf("Wrong Arguments\n");
        return EXIT_FAILURE;
    }

    //Input Variables
    char *input_filename = (char *) argv[1];
    char *output_filename_1 = (char *) argv[2];
    char *output_filename_2 = (char *) argv[3];

    //Read Input File
    double r_source = 0;
    double r = 0;
    double c = 0;
    //Attempt to Open Input File
    FILE *input_file_ptr = fopen(input_filename, "r");
    if (input_file_ptr == NULL)
    {
        printf("Error Opening Input File (Read_Header)\n");
        return EXIT_FAILURE;
    }

    int num_nodes = Read_Header(input_file_ptr,&r_source, &r,&c);

    //Write Empty File
    if (num_nodes == 0)
    {
        FILE *fprt_1 = fopen(output_filename_1, "w");
        FILE *fprt_2 = fopen(output_filename_2, "w");
        fclose(input_file_ptr);
        fclose(fprt_1);
        fclose(fprt_2);
        return 0;
    }
    else if(num_nodes == -1){  //Could not read file
        printf("Could not read input file.");
        return EXIT_FAILURE;
    }

    //printf("Source: %le\n",r_source);

    //Creating Post-Order Tree, and Printing Pre-Order.
    TreeNode *root_node = Create_Postorder(input_file_ptr, num_nodes);
    if(root_node == NULL){
        printf("Could not read Tree");
        return EXIT_FAILURE;
    }


    //PREORDER PRINT
//    printf("Preorder Print\n");
    //Attempt to Open Output File 1
    FILE *output_1_file_ptr = fopen(output_filename_1, "w");
    if (output_1_file_ptr == NULL)
    {
        printf("Error Opening Output File 1 (Preorder Print)\n");
        return EXIT_FAILURE;
    }
    printPreorder(root_node,output_1_file_ptr, num_nodes);
//    fclose(output_1_file_ptr);



    //DELAY PRINTING
//    printf("Delay Print\n");
    //Attempt to Open Output File 1
    FILE *output_2_file_ptr = fopen(output_filename_2, "w");
    if (output_2_file_ptr == NULL)
    {
        printf("Error Opening Output File 2 (Delay Print)\n");
        return EXIT_FAILURE;
    }
    Determine_CR(root_node, 0, c, r, r_source);
    Determine_CD(root_node);
    int write_delay_file = Determine_Time_Delay(root_node, 0, output_2_file_ptr);
    if(write_delay_file == 0){
        return EXIT_FAILURE;
    }
    fclose(output_2_file_ptr);

    //FREE TREE MEMORY
    Free_Tree_Helper(root_node);//Error Here due to determine capacitance error.

    return EXIT_SUCCESS;
}

