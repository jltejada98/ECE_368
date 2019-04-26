//
// Created by Jose Luis Tejada on 2019-03-25.
//

#include "shell_list.h"
#include "sequence.h"
#include <stdio.h>
#include <stdlib.h>

Node *List_Load_From_File(char *filename, int * size_list)
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
    * size_list = (file_size / sizeof(long));

    //If file empty do we allocate memory anyways?
    if (* size_list == 0)
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

    for (int i = 1; i < *size_list; ++i)
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

Node *List_Shellsort(Node *list, double *n_comp, int size)
{
    //Sequence Generation
    int seq_size = 0;
    long *sequence = Generate_2p3q_Seq(size, &seq_size);

    if (sequence == NULL)
    {
        printf("Error Generating Sequence\n");
        return NULL;
    }

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
            temp_list->node = Helper_Insertion_Sort_D(temp_list->node, n_comp);
            temp_list = temp_list->next;
        }

        //Merge all Sublists
        list = Helper_Merge_List(current_k, size, k_sublist);

    }
    //Perform k = 1 Insertion sort
    list = Helper_Insertion_Sort_A(list, n_comp);

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
            //NEW METHOD, ADDING NODES AT BEGGINING OF LIST.
            head = temp_node->next;
            temp_node->next = temp_node_list;
            temp_list->node = temp_node;


            //Increment Next Node to be added
            temp_node = head;
            temp_list = temp_list->next;
            if (temp_list != NULL)
            {
                temp_node_list = temp_list->node;
            }
            ++node_index;
            ++k_index;
        }
        //Start back at begging of List
        k_index = 0;
        temp_list = list_head;
        temp_node_list = temp_list->node; //First Node of List.
    }


    return list_head;
}

Node * Helper_Insertion_Sort_D(Node* head, double *n_comp)
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
            if(temp_3->value < head->value) //Original temp_3->value > head->value
            {
                temp_2 = head;
                ++(*n_comp);
                while ((temp_2->next != NULL) && (temp_3->value < temp_2->next->value)) //Original temp_3->value > temp_2->next->value
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
    temp_list_node = temp_list->node;

    int n_index = 1;
    int k_index = 1;

    while(n_index < size) //Do for all elements
    {
        while((k_index < k) && (n_index < size)) //Iterate through k sublists
        {
            //Select Node to Add to Merged List.
            // New Method adding nodes at beggining of merged head.
            temp_list->node = temp_list_node->next;
            merged_temp = temp_list_node;
            merged_temp->next = merged_head;

            //Merged Temp.
            merged_head = merged_temp;
            temp_list = temp_list->next; //Moving to Next item in list.
            if(temp_list != NULL){
                temp_list_node = temp_list->node;
            }
            ++n_index;
            ++k_index;
        }
        //Start Back at begging of list.
        k_index = 0;
        temp_list = head;
        temp_list_node = temp_list->node;
    }

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
}

Node * Helper_Insertion_Sort_A(Node* head, double *n_comp)
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
            if(temp_3->value > head->value) //Original temp_3->value > head->value
            {
                temp_2 = head;
                ++(*n_comp);
                while ((temp_2->next != NULL) && (temp_3->value > temp_2->next->value)) //Original temp_3->value > temp_2->next->value
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


