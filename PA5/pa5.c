
#include "sorting.h"

int main(int argc, char const *argv[]) {
    //Checking amount of time
    clock_t t = clock();

    if(argc != 4){
        printf("Incorrect Arguments.");
        return EXIT_FAILURE;
    }

   //Variables
    int num_longs = 0;
    const char *option = argv[1];
    char *input_filename = (char *) argv[2];
    char *output_filename = (char *) argv[3];


    if(!strcmp(option, "-m")){ //Perform Mergesort
        long *read_array = Array_Load_From_File(input_filename, &num_longs);

        //Determine if Proper Reading of File.
        if(num_longs == 0){ //Empty Input File
            //Open Output File
            FILE *output_file_ptr = fopen(output_filename, "w");
            if (output_file_ptr == NULL)
            {
                printf("Error Opening Output File\n");
                return EXIT_FAILURE;
            }
            fclose(output_file_ptr);
        }
        else if(num_longs == -1){
            return EXIT_FAILURE;
        }

        //Perform Sorting on Array.
        Merge_Sort(read_array,num_longs);

        //Save Array to array.
        int written_nums = Array_Save_To_File(output_filename, read_array,num_longs);

        //Check if num_written
        if(written_nums != num_longs){
            printf("Error Writting to File");
            return EXIT_FAILURE;
        }

        //Checking time
        t = clock() - t;
        double time_taken = ((double)t) / CLOCKS_PER_SEC;
        printf("Time Taken sec : %lf\n", time_taken);

        //Check Sorting
        int check_sort_flag = check_sorting(read_array, &num_longs);
        printf("Check_Sort:  %d\n", check_sort_flag);
        free(read_array);

    }
    else if(!strcmp(option, "-q")){ //Perform Quicksort
        long *read_array = Array_Load_From_File(input_filename, &num_longs);

        //Determine if Proper Reading of File.
        if(num_longs == 0){ //Empty Input File
            //Open Output File
            FILE *output_file_ptr = fopen(output_filename, "w");
            if (output_file_ptr == NULL)
            {
                printf("Error Opening Output File\n");
                return EXIT_FAILURE;
            }
            fclose(output_file_ptr);
        }
        else if(num_longs == -1){
            return EXIT_FAILURE;
        }

        //Perform Sorting on Array
        Quick_Sort(read_array, num_longs);

        //Save Array to array.
        int written_nums = Array_Save_To_File(output_filename, read_array,num_longs);

        //Check if num_written
        if(written_nums != num_longs){
            printf("Error Writting to File");
            return EXIT_FAILURE;
        }

        //Checking time
        t = clock() - t;
        double time_taken = ((double)t) / CLOCKS_PER_SEC;
        printf("Time Taken sec : %lf\n", time_taken);

        //Check Sorting
        int check_sort_flag = check_sorting(read_array, &num_longs);
        printf("Check_Sort:  %d\n", check_sort_flag);
        free(read_array);
    }
    else{
        printf("Incorrect -m/-q argument\n");
        return EXIT_FAILURE;
    }

    return 0;
}

//////////////////
//Load Functions//
//////////////////

long *Array_Load_From_File(char *filename, int *size){
    FILE *file_ptr = fopen(filename, "r");

    if (file_ptr == NULL)
    {
        printf("Error Opening Input File (Array)\n");
        *size = -1;
        return NULL;
    }

    //Determination of size of input file
    fseek(file_ptr, 0, SEEK_END);
    long file_size = ftell(file_ptr);
    *size = (file_size / sizeof(long));

    //If file empty do we allocate memory anyways?
    if (*size == 0)
    {
        return NULL;
    }

    //Allocating Memory for array
    long *file_array = malloc(sizeof(long) *  (*size) );

    if (file_array == NULL)
    {
        printf("Error Allocating Input Array Memory\n");
        *size = -1;
        return NULL;
    }

    //Reading File
    fseek(file_ptr, 0, SEEK_SET);
    int longs_read = fread(file_array, sizeof(long), (*size), file_ptr);

    if (longs_read != (*size))
    {
        printf("Error Reading Input File\n");
        free(file_array);
        *size = -1;
        return NULL;
    }

    fclose(file_ptr);
    return file_array;
}

int Array_Save_To_File(char *filename, long *array, int size){
    FILE *file_ptr = fopen(filename, "w");

    if (file_ptr == NULL)
    {
        printf("Error Opening Output File\n");
        return 0;
    }
    //Write to Array
    int num_written = fwrite(array, sizeof(long), size, file_ptr);

    fclose(file_ptr);

    return num_written;
}
