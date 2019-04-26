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
  int num_nodes = Read_Header(input_filename,&r_source, &r,&c);
  
  //Empty File
  if (num_nodes == 0)
  {
    FILE *fprt_1 = fopen(output_filename_1, "w");
    FILE *fprt_2 = fopen(output_filename_2, "w");
    fclose(fprt_1);
    fclose(fprt_2);
    return 0;
  }
  
  //printf("Source: %le\n",r_source);

  //Creating Post-Order Tree, and Printing Pre-Order.
  TreeNode *root_node = Create_Postorder(input_filename, num_nodes);
  printPreorder(root_node, output_filename_1);

  //Test Path Resistance and node capacitance function
  Determine_CR(root_node, 0, c, r, r_source);
  Determine_CD(root_node);
  Determine_Time_Delay_Helper(root_node, 0, output_filename_2);

  //Free TreeNode Memory
  Free_Tree_Helper(root_node);//Error Here due to determine capacitance error.
  return 0;
}

