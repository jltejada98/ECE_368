//
// Created by Jose Luis Tejada on 2019-04-15.
//

#include "seqpair.h"

rect * load_input(FILE * fptr, int ** seq_1, int ** seq_2, int * num_rect){
    //Determine number of elements
    int check_read = 0;
    check_read = fscanf(fptr, "%d\n", num_rect);
    if(check_read  != 1){
        printf("Incorrect Input File Format");
        *num_rect = -1;
        return NULL;
    }
    else if(*num_rect == 0){
        return NULL;
    }

    //Read rectangles and store into array.
    rect * rectangle_array = malloc(sizeof(rect) * (*num_rect));

    if(rectangle_array == NULL){
        printf("Could not allocate memory for rectangle array");
        return NULL;
    }

    int temp_label = 0;
    double temp_width = 0;
    double temp_height = 0;

    for (int i = 0; i < (*num_rect); ++i) {
        check_read = fscanf(fptr, "%d(%le,%le)\n", &temp_label, &temp_width, &temp_height);
        if (check_read != 3) { //Check for correct read format
            free(rectangle_array);
            printf("Incorrect Input File Format When Reading Rectangle Dimensions");
            *num_rect = -1;
            return NULL;
        }
        rectangle_array[i].label = temp_label;
        rectangle_array[i].width = temp_width;
        rectangle_array[i].height = temp_height;
        rectangle_array[i].x = 0;
        rectangle_array[i].y = 0;
        rectangle_array[i].indegree_x = 0;
        rectangle_array[i].indegree_y = 0;
        rectangle_array[i].next = NULL;
    }

    //Read Sequences and store into respective arrays
    //Sequence 1
    int * sequence_1 = malloc(sizeof(int) * (*num_rect));

    if(sequence_1 == NULL){
        printf("Could not allocate memory for seq_1 array");
        return NULL;
    }

    int temp_seq = 0;
    for (int j = 0; j < (*num_rect); ++j) {
        if(j == ((*num_rect) - 1 )){ //Reading Last Element
            check_read = fscanf(fptr,"%d\n", &temp_seq);
            if(check_read != 1){
                free(rectangle_array);
                free(sequence_1);
                printf("Incorrect Input File Format When Reading Sequence 1");
                *num_rect = -1;
                return NULL;
            }
            sequence_1[j] = temp_seq;
        } else{
            check_read = fscanf(fptr, "%d ", &temp_seq);
            if(check_read != 1){
                free(rectangle_array);
                free(sequence_1);
                printf("Incorrect Input File Format When Reading Sequence 1");
                *num_rect = -1;
                return NULL;
            }
            sequence_1[j] = temp_seq;
        }
    }

    //Sequence 2
    int * sequence_2 = malloc(sizeof(int) * (*num_rect));

    if(sequence_2 == NULL){
        printf("Could not allocate memory for seq_1 array");
        return NULL;
    }


    for (int j = 0; j < (*num_rect); ++j) {
        if(j == ((*num_rect) - 1 )){ //Reading Last Element
            check_read = fscanf(fptr,"%d\n", &temp_seq);
            if(check_read != 1){
                free(rectangle_array);
                free(sequence_1);
                free(sequence_2);
                printf("Incorrect Input File Format When Reading Sequence 2");
                *num_rect = -1;
                return NULL;
            }
            sequence_2[j] = temp_seq;
        } else{
            check_read = fscanf(fptr, "%d ", &temp_seq);
            if(check_read != 1){
                free(rectangle_array);
                free(sequence_1);
                free(sequence_2);
                printf("Incorrect Input File Format When Reading Sequence 2");
                *num_rect = -1;
                return NULL;
            }
            sequence_2[j] = temp_seq;
        }
    }

    *seq_1 = sequence_1;
    *seq_2 = sequence_2;

    return rectangle_array;
}


int Process_Input_Horizontal(int * seq_1, int * seq_2, rect * rectangle_array, int * index_1, int *index_2, int size){
    //Horizontal Processing: Connections are those that appear after a given item in both lists.
    rect * temp_pointer = NULL;
    int l_index = 0;
    int s_index = 0;
    int l_sequence = 0;

    for (int check_index = 0; check_index < size; ++check_index) { //Iterate through all labels
        if(index_1[check_index] > index_2[check_index]){ //Determines largest index of item in both sequences.
            l_index = index_1[check_index];
            s_index = index_2[check_index];
            l_sequence = 1;
        }
        else{
            l_index = index_2[check_index];
            s_index = index_1[check_index];
            l_sequence = 2; //Consider Removal
        }
        if(l_index >= (size - 1)){ //Determines if largest index is the last index, therefore only target connection.
            rectangle_array[check_index].next = NULL;
        }
        else {
            int potential_connection = 0;
            int index_to_check = 0;
            temp_pointer = &rectangle_array[check_index];
            if(l_sequence == 1){ //Smaller sequence is sequence 1.
                for (int pc_index = l_index + 1; pc_index < size; ++pc_index) { //Iterate through potential connections
                    potential_connection = seq_1[pc_index] - 1;
                    index_to_check = index_2[potential_connection];
                    if(index_to_check > s_index){ //Potential Connection is Possible.
                        //Increment In-degree of added node
                        rectangle_array[potential_connection].indegree_x += 1;
                        //Add new connection
                        temp_pointer->next = Add_Edge(rectangle_array[potential_connection]);
                        if(temp_pointer->next == NULL){//Add Check for if Memory Allocation is null for new edge.
                            printf("Memory Allocation Error\n");
                            return 0;
                        }
                        temp_pointer = temp_pointer->next;
                    }
                }
                temp_pointer->next = NULL;
            }else{
                for (int pc_index = l_index + 1; pc_index < size; ++pc_index){ //Iterate through potential connections
                    potential_connection = seq_2[pc_index] - 1;
                    index_to_check = index_1[potential_connection];
                    if(index_to_check > s_index){ //Potential Connection is Possible.
                        //Increment In-degree of added node
                        rectangle_array[potential_connection].indegree_x += 1;
                        //Add new connection
                        temp_pointer->next = Add_Edge(rectangle_array[potential_connection]);
                        if(temp_pointer->next == NULL){//Add Check for if Memory Allocation is null for new edge.
                            printf("Memory Allocation Error\n");
                            return 0;
                        }
                        temp_pointer = temp_pointer->next;
                    }
                }
                temp_pointer->next = NULL;
            }
        }
    }

    return 1;
}


int Process_Input_Vertical(int * seq_1, int * seq_2, rect * rectangle_array, int * index_1, int *index_2, int size){
    //Vertical Processing: Connections are those that appear before a given item in the first list but after the item in the second one.
    //Define temp
    rect * temp_pointer = NULL;
    //Indices
    int seq_1_index = 0;
    int seq_2_index = 0;

    for (int check_index = 0; check_index < size; ++check_index) {
        seq_1_index = index_1[check_index];
        seq_2_index = index_2[check_index];

        if(seq_1_index == 0){ //No items before in 1st sequence indicate no possible connection.
            rectangle_array[check_index].next = NULL;
        }
        else if(seq_2_index >= (size - 1)){ //No items after in 2nd sequence indicate no possible connection
            rectangle_array[check_index].next = NULL;
        }
        else {
            int potential_connection = 0;
            int index_to_check = 0;
            temp_pointer = &rectangle_array[check_index];
            if(seq_1_index < ((size - 1) - seq_2_index)){ //Determines which sequence is smaller to iterate along. //Iterate in sequence 1.
                for (int pc_index = 0; pc_index < seq_1_index ; ++pc_index) { //Check connections before in 1st sequence
                    potential_connection = seq_1[pc_index] - 1;
                    index_to_check = index_2[potential_connection];
                    if(index_to_check > seq_2_index){ //Potential Connection is Possible
                        //Increment In-degree
                        rectangle_array[potential_connection].indegree_y += 1;
                        //Add new Node
                        temp_pointer->next = Add_Edge(rectangle_array[potential_connection]);
                        if(temp_pointer->next == NULL){//Add Check for if Memory Allocation is null for new edge.
                            printf("Memory Allocation Error\n");
                            return 0;
                        }
                        //Increment In-degree of added node
                        temp_pointer = temp_pointer->next;
                    }
                }
                temp_pointer->next = NULL;
            }
            else{ //Iterate on Sequence 2.
                for (int pc_index = seq_2_index + 1; pc_index < size; ++pc_index) {
                    potential_connection = seq_2[pc_index] - 1;
                    index_to_check = index_1[potential_connection];
                    if(index_to_check < seq_1_index){ //Potential Connection is Possible
                        //Increment In-degree of added node
                        rectangle_array[potential_connection].indegree_y += 1;
                        //Add new Node
                        temp_pointer->next = Add_Edge(rectangle_array[potential_connection]);
                        if(temp_pointer->next == NULL){//Add Check for if Memory Allocation is null for new edge.
                            printf("Memory Allocation Error\n");
                            return 0;
                        }
                        temp_pointer = temp_pointer->next;
                    }
                }
                temp_pointer->next = NULL;
            }
        }
    }

    return 1;
}


void DFS_Horizontal(rect * rectangle_horiz, int size){
//    Increment degree of nodes from start.
    rect *start = malloc(sizeof(rect));
    rect *temp = start;
    for (int i = 0; i < size; ++i) {
        if (rectangle_horiz[i].indegree_x == 0) {
            rectangle_horiz[i].indegree_x = 1;
            temp->next = Add_Edge(rectangle_horiz[i]);
            temp = temp->next;
        }
    }

    printf("Rectangle Check\n");
    for (int i = 0; i < size ; ++i) {
        printf("Rectangle: %d, IN: (%d) ->", rectangle_horiz[i].label,rectangle_horiz[i].indegree_x);
        rect *temp = rectangle_horiz[i].next;
        while(temp != NULL){
            printf("%d ->", temp->label);
            temp = temp->next;
        }
        printf("\n");
    }

    //Print start node
    rect *temp1 = start;
    while(temp1 != NULL){
        printf("%d ->\n", temp1->label);
        temp1 = temp1->next;
    }

    //Possibility must sort nodes.
    temp1 = start->next;
    while(temp1 != NULL){
        dfs_horizontal(rectangle_horiz, temp1->label - 1, 0);
        temp1 = temp1->next;
    }

}

void dfs_horizontal(rect *rectangle_horiz, int rect_index, double distance){
    rect *current = &rectangle_horiz[rect_index];
    rect *next = current->next;

    if(current->x < distance){
        current->x = distance;
    }
    (current->indegree_x)--;
    if(current->indegree_x <= 0){
        int updated_distance = 0; //Update Current Distance, takes care of indegree 0 node.
        if((distance + current->x) < (distance + current->width)){
            updated_distance = distance + current->width;
        }
        else{
            updated_distance = distance + current->x;
        }
        while(next != NULL){
            int next_index = next->label - 1;
            //Change distance + current->width to distance + current->x
            dfs_horizontal(rectangle_horiz, next_index, updated_distance);
            next = next->next;
        }
    }
}

void DFS_Vertical(rect * rectangle_array, int size){
    //Increment degree of nodes from start.
    for (int i = 0; i < size; ++i) {
        if (rectangle_array[i].indegree_y == 0) {
            rectangle_array[i].indegree_y = 1;
        }
    }


    //Visit All Nodes and recursively call dfs.
    for (int array_index = 0; array_index < size; ++array_index) {
        dfs_vertical(rectangle_array,array_index, 0);
    }

}

void dfs_vertical(rect *rectangle_array, int rect_index, double distance){
    rect *current = &rectangle_array[rect_index];
    rect *next = current->next;

    if(current->y < distance){
        current->y = distance;
    }
    (current->indegree_y)--;
    if(current->indegree_y == 0){
        int updated_distance = 0; //Update Current Distance, takes care of indegree 0 node.
        if((distance + current->y) < (distance + current->height)){
            updated_distance = distance + current->height;
        }
        else{
            updated_distance = distance + current->y;
        }
        while(next != NULL){
            int next_index = next->label - 1;
            //Change distance + current->width to distance + current->x
            dfs_horizontal(rectangle_array, next_index, updated_distance);
            next = next->next;
        }
    }
}

int write_to_file(rect* rectangle_horizontal, rect * rectangle_vertical, FILE *fptr, int size){
    int label = 0;
    double x = 0;
    double y = 0;
    int check_write = 0;
    int rect_index = 0;

    for (; rect_index < size; ++rect_index) {
        label = rectangle_horizontal[rect_index].label;
        x = rectangle_horizontal[rect_index].x;
        y = rectangle_vertical[rect_index].y;
        check_write = fprintf(fptr, "%d(%le,%le)\n", label, x, y);
        if(check_write <= 0){
            printf("Error writing to file");
            return rect_index;
        }
    }
    return rect_index;
}


void Pre_Processing(int ** seq_1, int ** seq_2, int ** index_sequence_1, int ** index_sequence_2, int size){
    //Preprocessing (Make sequences contain the index of the element at the certain index)
    int * index_1 = malloc(sizeof(int) * size);
    int * index_2 = malloc(sizeof(int) * size);

    for (int i = 0; i < size ; ++i) {
        index_1[(*seq_1)[i] - 1] = i;
        index_2[(*seq_2)[i] - 1] = i;
    }

    *index_sequence_1 = index_1;
    *index_sequence_2 = index_2;
}


rect * Pre_Processing_Rectangles(rect * rectangle, int size){
    rect * rectangle_copy = malloc(sizeof(rect) *  size);

    if(rectangle_copy == NULL){
        return  NULL;
    }

    //Instatiate Start node
    for (int i = 0; i < size; ++i) {
        rectangle_copy[i].label = rectangle[i].label;
        rectangle_copy[i].width = rectangle[i].width;
        rectangle_copy[i].height = rectangle[i].height;
        rectangle_copy[i].x = rectangle[i].x;
        rectangle_copy[i].y = rectangle[i].y;
        rectangle_copy[i].indegree_x = rectangle[i].indegree_x;
        rectangle_copy[i].indegree_y = rectangle[i].indegree_y;
        rectangle_copy[i].next = NULL;
    }

    return  rectangle_copy;
}


rect * Add_Edge(rect rect_node){
    rect * new_edge = malloc(sizeof(rect));
    if(new_edge == NULL){
        return NULL;
    }
    new_edge->label = rect_node.label;
    new_edge->width = rect_node.width;
    new_edge->height = rect_node.height;
    new_edge->x = 0;
    new_edge->y = 0;
    new_edge->indegree_x = rect_node.indegree_x;
    new_edge->indegree_x = rect_node.indegree_y;
    new_edge->next = NULL;

    return new_edge;
}

void free_rectangle_array(rect * rectangle, int size){
    rect *temp = NULL;
    rect *curr = NULL;
    for (int i = 0; i < size; ++i) {
        curr = rectangle[i].next;
        while(curr != NULL){
            temp = curr->next;
            free(curr);
            curr = temp;
        }
    }
    free(rectangle);
}
