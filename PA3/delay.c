#include "pa3.h"


///////////////////////////////
/////Function Definitions//////
///////////////////////////////

//Note: Check set parent node to null for root.
//Note: Initialize resistance path to 0 in main.

//Determines capacitances of all nodes in tree.
void Determine_CR(TreeNode *node_i,double WL, double WC, double WR, double r_path)
{
  if (node_i == NULL)
  {
    return;
  }

  if (node_i->label != -1)
  {
    node_i->cap += (WL*WC) / 2.0;
    node_i->r_path += (WL*WR) + r_path;
    return;
  }
  else
  {
    node_i->cap += (WL * WC) / 2.0;
    node_i->cap += (WC * node_i->length_l) / 2.0;
    node_i->cap += (WC * node_i->length_r) / 2.0;
    node_i->r_path = r_path + (WL * WR);
    Determine_CR(node_i->left,node_i->length_l , WC, WR, r_path + WL*WR);
    Determine_CR(node_i->right,node_i->length_r, WC, WR, r_path);
  }

  return;
}

void Determine_CD(TreeNode * node)
{
  if (node == NULL)
  {
    return;
  }

  if (node->label != -1)
  {
    node->c_down = node->cap;
    return;
  }
  else
  {
    Determine_CD(node->left);
    Determine_CD(node->right);
    node->c_down = (node->left->c_down) + (node->right->c_down) + (node->cap);
  }
}

void Determine_Time_Delay_Helper(TreeNode * node, double time, char *filename)
{
  if (node == NULL)
  {
    return;
  }

  if (node->label != -1)
  {
    double leaf_time = time / (node->r_path) + (node->r_path)*(node->r_path);

    //Write leaf time to binary
    FILE *file_ptr = fopen(filename, "w");

    if (file_ptr == NULL)
    {
      printf("Error Opening Output File\n");
      fclose(file_ptr);
      return;
    }
    
    //Write to Array
    int num_written  = fwrite(&(node->label), sizeof(int),1, file_ptr);
    num_written += fwrite(&(leaf_time), sizeof(double), 1, file_ptr);

    // printf("%d\n",num_written);
    if (num_written != 2)
    {
      printf("Error Writing to output File\n");
      fclose(file_ptr);
      return;
    }

    fclose(file_ptr);
    return;
  }
  else
  {
    double temptime = node->r_path * node->r_path * (node->c_down - (node->left->c_down));
    Determine_Time_Delay_Helper(node->left, (time + temptime), filename);
    temptime = node->r_path * node->r_path * (node->c_down - (node->right->c_down));
    Determine_Time_Delay_Helper(node->right, (time + temptime), filename);
  }
}

