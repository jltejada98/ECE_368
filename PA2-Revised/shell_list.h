//
// Created by Jose Luis Tejada on 2019-03-25.
//

#ifndef PA2_REVISED_SHELL_LIST_H
#define PA2_REVISED_SHELL_LIST_H
typedef struct _Node {
    long value;
    struct _Node *next;
} Node;

//Structure Declarations
typedef struct List {
    Node *node;
    struct List *next;
} List;


Node *List_Load_From_File(char *filename, int * size_list);
int List_Save_To_File(char *filename, Node *list);
Node *List_Shellsort(Node *list, double *n_comp, int size);

//Helper Function Declarations
Node * Helper_CreateNode(long);
List * Helper_CreateList(Node *);
List * Helper_Split_List(int, int, Node *);
Node * Helper_Insertion_Sort_D(Node *, double *);
Node * Helper_Merge_List(int, int, List *);
void Helper_Delete_List(List *);
Node * Helper_Insertion_Sort_A(Node* head, double *n_comp);



#endif //PA2_REVISED_SHELL_LIST_H
