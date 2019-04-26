//
// Created by Jose Luis Tejada on 2019-03-27.
//

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
        Determine_CR(node_i->left,node_i->length_l , WC, WR, r_path + (WL*WR));
        Determine_CR(node_i->right,node_i->length_r, WC, WR, r_path + (WL*WR));
    }
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

int Determine_Time_Delay(TreeNode * node, double time, FILE *file_ptr)
{
    if (node == NULL)
    {
        return 1;
    }

    if (node->label != -1)
    {
        //Write to Array
        double leaf_time = (time / node->r_path) + (node->r_path * node->c_down);
//        printf("%d(%le)\n", node->label,leaf_time );
        int num_written  = fwrite(&(node->label), sizeof(int),1, file_ptr);
        num_written += fwrite(&(leaf_time), sizeof(double), 1, file_ptr);
        if (num_written != 2)
        {
            printf("Error Writing to output delay file\n");
            fclose(file_ptr);
            return 0;
        }

        return 1;
    }
    else
    {
        double temptime = node->r_path * node->r_path * (node->c_down - (node->left->c_down));
        Determine_Time_Delay(node->left, (time + temptime), file_ptr);
        temptime = node->r_path * node->r_path * (node->c_down - (node->right->c_down));
        Determine_Time_Delay(node->right, (time + temptime), file_ptr);
    }
    return 1;
}