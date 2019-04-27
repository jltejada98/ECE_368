#include "seqpair.h"

int main(int argc, char const *argv[]) {
    //Check Program Arguments
    if(argc != 3){
        printf("Incorrect Arguments.");
        return EXIT_FAILURE;
    }

    char *input_filename = (char *) argv[1];
    char *output_filename = (char *) argv[2];

    //Attempt to open Input File
    FILE *fptr_input = fopen(input_filename, "r");

    if(fptr_input == NULL){
        printf("Could not open input file");
        return EXIT_FAILURE;
    }

    //Read Rectangle array
    int * seq_1 = NULL;
    int * seq_2 = NULL;
    int num_rect = 0;

    rect *rectangle_array = load_input(fptr_input, &seq_1, &seq_2, &num_rect);
    fclose(fptr_input); //Close Input File

    if(num_rect == -1){ //Incorrect format of input file.
        return EXIT_FAILURE;
    }
    else if(num_rect == 0){ //Create empty output file
        //Attempt to open Output File
        FILE *fptr_output = fopen(output_filename, "w");

        if(fptr_output == NULL){
            printf("Could not open output file");
            return EXIT_FAILURE;
        }
        return  EXIT_SUCCESS;
    }
    else if(rectangle_array == NULL){
        return  EXIT_FAILURE;
    }

    //Pre_Processing Operations
    int * index_sequence_1 = NULL;
    int * index_sequence_2 = NULL;
    Pre_Processing(&seq_1, &seq_2, &index_sequence_1, &index_sequence_2, num_rect);
    //Create Copy of Rectangle.
    rect *rectangle_copy =  Pre_Processing_Rectangles(rectangle_array, num_rect);

    if(rectangle_copy == NULL){
        printf("Could not Allocate Auxilary Memory");
        return EXIT_FAILURE;
    }

    //Process input file by creating adjancency lists.
    int flag = 0;
    flag = Process_Input_Horizontal(seq_1, seq_2, rectangle_array, index_sequence_1, index_sequence_2, num_rect);
    if(flag == 0){
        free(index_sequence_1);
        free(index_sequence_2);
        free(seq_1);
        free(seq_2);
        free_rectangle_array(rectangle_array, num_rect);
        free_rectangle_array(rectangle_copy, num_rect);
        return EXIT_FAILURE;
    }

    flag = Process_Input_Vertical(seq_1, seq_2, rectangle_copy, index_sequence_1, index_sequence_2, num_rect);
    if(flag == 0){
        free(index_sequence_1);
        free(index_sequence_2);
        free(seq_1);
        free(seq_2);
        free_rectangle_array(rectangle_array, num_rect);
        free_rectangle_array(rectangle_copy, num_rect);
        return EXIT_FAILURE;
    }
//    //Determine Longest path to rectangles in HCG using DFS.
    DFS_Horizontal(rectangle_array, num_rect);

    for (int j = 0; j < num_rect ; ++j) {
        printf("Label : %d, X= %le\n",rectangle_array[j].label, rectangle_array[j].x);
    }

    printf("Rectangle Check Copy\n");
    for (int i = 0; i < num_rect ; ++i) {
        printf("Rectangle: %d, IN: (%d) ->", rectangle_copy[i].label,rectangle_copy[i].indegree_y);
        rect *temp = rectangle_copy[i].next;
        while(temp != NULL){
            printf("%d ->", temp->label);
            temp = temp->next;
        }
        printf("\n");
    }

//    //Determine Longest path to rectangles in VCG using DFS.
    DFS_Vertical(rectangle_copy, num_rect);

    for (int j = 0; j < num_rect ; ++j) {
        printf("Label : %d, Y= %le\n",rectangle_copy[j].label, rectangle_copy[j].y);
    }

    //Attempt to open Output File
    FILE *fptr_output = fopen(output_filename, "w");

    if(fptr_output == NULL){
        printf("Could not open output file");
        return EXIT_FAILURE;
    }

    //Write Output File.
    int check_written = write_to_file(rectangle_array, rectangle_copy,fptr_output, num_rect);

    if(check_written < num_rect){
        //Free Sequences
        free(seq_1);
        free(seq_2);
        free(index_sequence_1);
        free(index_sequence_2);
        //Free Horizontal Array
        free_rectangle_array(rectangle_array, num_rect);
        //Free Vertical Array
        free_rectangle_array(rectangle_copy, num_rect);
        fclose(fptr_output); //Close Output File.
        return EXIT_FAILURE;
    }

    //Free Sequences
    free(seq_1);
    free(seq_2);
    free(index_sequence_1);
    free(index_sequence_2);
    //Free Horizontal Array
    free_rectangle_array(rectangle_array, num_rect);
    //Free Vertical Array
    free_rectangle_array(rectangle_copy, num_rect);
    fclose(fptr_output); //Close Output File.

    return EXIT_SUCCESS;
}
