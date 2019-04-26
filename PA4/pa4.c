#include "pa4.h"

int main(int argc, char const *argv[]) {
    //Variables
    const char *option = argv[1];
    char *input_filename = (char *) argv[2];
    char *output_filename = (char *) argv[3];

    //Check Arguments
    if (!strcmp(option, "-b") && (argc != 4)){
        printf("Wrong Arguments\n");
        return EXIT_FAILURE;
    }

    if(!strcmp(option, "-e") && (argc != 3)){
        printf("Wrong Arguments\n");
        return EXIT_FAILURE;
    }



    //Check Option
    if(!strcmp(option, "-b")){ //Building Height Balanced Tree
        //Attempt to open input file
        FILE *input_fptr = fopen(input_filename, "r");

        if(input_fptr == NULL){
            printf("-1\n");
            return EXIT_FAILURE;
        }

        //Construct Tree
        long tree_size = 0;
        int op_flag = 0;
        TreeNode *root_node = Build_Load_From_File(input_fptr, &tree_size, &op_flag);

        //Determine if problems when reading/constructing the tree.
        if(op_flag != 1){
            printf("%d\n", op_flag);
            return EXIT_FAILURE;
        }
        else{
            printf("%d\n", op_flag);
        }

        //Close input file header
        fclose(input_fptr);

        //Attempt to open output file.
        FILE *out_fptr = fopen(output_filename, "w");

        if(out_fptr == NULL){

            return  EXIT_FAILURE;
        }

        //Write File to output file
        Build_Write_To_File(root_node, out_fptr);

        //Memory Management.
        free_tree(root_node);
        fclose(out_fptr);
    }
    else if(!strcmp(option, "-e")){
        //Attempt to open input file
        FILE *input_fptr = fopen(input_filename, "r");
        int code_arr[3] = {-1,0,0};

        if(input_fptr == NULL){
            printf("%d,%d,%d\n",code_arr[0], code_arr[1], code_arr[2]);
            return EXIT_FAILURE;
        }
        //File opened
        code_arr[0] += 1;

        //Determination of input size
        fseek(input_fptr, 0, SEEK_END);
        long file_size = ftell(input_fptr);
        long input_size = (file_size / (sizeof(int) + sizeof(char)));

        if(input_size == 0){ //Empty File-->Wrong Format
            printf("%d,%d,%d\n",code_arr[0], code_arr[1], code_arr[2]);
            return EXIT_FAILURE;
        }

        //Read file and build tree
        fseek(input_fptr, 0, SEEK_SET);
        TreeNode *root = NULL;
        int read_successful = 0;
        root = Build_Tree(root,input_fptr, 0, input_size, &read_successful);
        code_arr[0] = read_successful;

        //Close file pointer
        fclose(input_fptr);

        if(code_arr[0] == 0){ //Wrong Format While reading file
            printf("%d,%d,%d\n",code_arr[0], code_arr[1], code_arr[2]);
            free_tree(root);
            return EXIT_FAILURE;
        }

        //Determine if BST, should we allow for repeated values?
        code_arr[1] = Evaluate_BST(root, INT_MIN, INT_MAX);
        //Determine if Height Balanced BST (Consider using Post-Order Balancing Determination)
        code_arr[2] = Evaluate_Balance(root);

        printf("%d,%d,%d\n",code_arr[0], code_arr[1], code_arr[2]);
        free_tree(root);
    }
    else {
        printf("Incorrect -l/-a argument\n");
        return EXIT_FAILURE;
    }


    return 0;
}
