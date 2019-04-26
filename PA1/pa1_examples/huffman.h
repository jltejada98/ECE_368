//Structures
typedef struct 
{
  char value;
  long freq;
}CharFreq;

typedef struct TNode
{
  struct TNode* left;
  struct TNode* right;
  char value; // character
  long freq;  // frequency
}TreeNode;

typedef struct LNode
{
  struct LNode *next;
  TreeNode* treenode;
}ListNode;


//Function Declarations
CharFreq * count_characters(const char *filename_in, const char *filename_out, long * num_unique_chars);
void generate_tree(CharFreq *char_arr, ListNode *list_head, long * num_unique_chars);
void bubble_sort_char(CharFreq *char_arr,long * num_unique_chars);
ListNode * CreateNode(char val, long freq, TreeNode *left, TreeNode *right);
TreeNode * CreateNode_t(char val, long freq, TreeNode *left, TreeNode *right);
