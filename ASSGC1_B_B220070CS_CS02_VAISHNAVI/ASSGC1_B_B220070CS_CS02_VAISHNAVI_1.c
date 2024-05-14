//Vaishnavi B220070CS: Cycle 1 Part B - Question 1

#include <stdio.h>
#include <stdlib.h>

struct binary_node {
    int data;
    struct binary_node *left, *right;
};

typedef struct binary_node* node;

struct que_list {
    node data[100];
    int front;
    int rear;
};

typedef struct que_list* queue;

node create_new (int key)                
{
    node new = (node)malloc(sizeof(struct binary_node));
    new->data = key;
    new->left = NULL;
    new->right = NULL;
    return new;
}

int empty_check (queue que)
{
    if (que->front == -1)
       return 1;
    else 
       return 0;
}

void enqueue (queue Q, node num)
{
    if (empty_check(Q) == 1)
    {
        Q->front = 0;
        Q->rear = 0;
    }
    else 
        Q->rear = (Q->rear + 1)%100;

    if (Q->front == (Q->rear + 1)%100)
       exit (0);
    Q->data[Q->rear] = num;
}

node dequeue (queue Q)
{
    node temp = Q->data[Q->front];
    if (Q->front == Q->rear)
    {
        Q->front = -1;
        Q->rear = -1;
    }
    else
    {
        Q->front = (Q->front + 1)%100;
    }
    return temp;
}

node construct_tree (int inorder[], int preorder[], int low, int high, int* index)        //Function to construct tree from the given inorder and preorder traversals
{
    if (low > high)
    {  return NULL;  }

    node new = create_new (preorder[(*index)++]);               //The first element in preorder is always the root

    int i;
    for (i = low; i <= high; i++)
    {
        if (inorder[i] == new->data)                           //From the inorder traversal, we can get the integers to left and right of the root
            break;
    }

    new->left = construct_tree(inorder, preorder, low, i-1, index);
    new->right = construct_tree (inorder, preorder, i+1, high, index);

    return new;
}

node binary_tree (int in[], int pre[], int len)
{
    int index = 0;
    return construct_tree (in, pre, 0, len-1, &index);
}

void postorder_traverse (node root)         //PostOrder(T)
{
    if (root == NULL)
       return;

   else
   {
       postorder_traverse (root->left);
       postorder_traverse (root->right);
       printf ("%d ", root->data);
   }
}

int check_max (int a, int b)
{
    return (a>b)? a : b;
}

int height (node root)                     //Function to calculate the height of any node by checking the maximum of heights of its left and right subtrees
{
    if (root == NULL)
       return 0;

    int left_h = height(root->left);
    int right_h = height(root->right);

    //printf ("%d %d\n", left_h, right_h);
    int final = check_max(left_h, right_h) + 1;
    return final;
}

void print_level(node tree, int level, int direction)              //Function to print a particular level based on its direction (Left to Right or vice versa)
{
    if (tree == NULL)
       return;

    if (level == 1)
       printf ("%d ", tree->data);

    else
    {
        if (direction)
        {
            print_level(tree->left, level-1, direction);
            print_level(tree->right, level-1, direction);
        }
        else
        {
            print_level(tree->right, level-1, direction);
            print_level(tree->left, level-1, direction);
        }
    }
}

void zigzag_traverse (node root)            //ZIG_ZIG(T)
{
    if (root == NULL)
       return;

    int depth = height(root);
    int i;
    int direction = 1;

    for (i = 1; i<=depth; i++)
    {
        print_level (root, i, direction);
        direction = !direction;
    }

    direction = 1;
}

void max_element (node root)             //Level_Max(T)
{
    if (root == NULL)
        return;
    
    queue Q = (queue)malloc(sizeof(struct que_list));
    Q->front = -1;
    Q->rear = -1;

    enqueue (Q, root);

    while (empty_check(Q) == 0)
    {
       int level_max = -1;
       int count = Q->rear - Q->front +1;

       for (int i=0; i<count; i++)
       {
        node temp = dequeue(Q);
        level_max = check_max (level_max, temp->data);

        if (temp->left != NULL)
        {
            enqueue(Q, temp->left);
        }
        if (temp->right != NULL)
        {
            enqueue(Q, temp->right);
        }
       }
       printf ("%d ", level_max);
    }
   
    free(Q);
}

int diameter_tree (node root)             //Diameter(T)
{
    if (root == NULL)
       return 0;

   int left = height(root->left);
   int right = height(root->right);

   int diameter = left+right+1;
   int left_d = diameter_tree(root->left);
   int right_d = diameter_tree(root->right);
   //printf ("%d %d\n", left_d, right_d);

   int max = check_max(left_d, right_d);

   return check_max(diameter, max);
}

int leaf_check (node check)            //Function to check if a particular node is a leaf node
{
    if (check == NULL)
       return 0;
    else if (check->left == NULL && check->right == NULL)
       return 1;
    else
       return 0;
}

int leftleaf_sum (node root)           //Left_Leaf_Sum(T)
{
    int sum = 0;
    if (root == NULL)
       return 0;

    if (root->left)
    {
        if (leaf_check(root->left))
           sum += root->left->data;
        else 
           sum += leftleaf_sum (root->left);
    }

    sum += leftleaf_sum (root->right);
    return sum;
}

int main ()
{
    int n;
    scanf ("%d", &n);
    getchar();
   
    int inorder[n];
    int preorder[n];
   
    for (int i=0; i<n; i++)
    {
        scanf ("%d", &inorder[i]);
    }
    for (int j=0; j<n; j++)
    {
        scanf ("%d", &preorder[j]);
    }
   
    node root = binary_tree (inorder, preorder, n);

    char value;
    while (1) 
    {
        scanf (" %c", &value);
        switch (value)
        {
            case 'p': postorder_traverse (root);
                      printf ("\n");
                      break;

            case 'z': zigzag_traverse (root);
                      printf ("\n");
                      break;

            case 'm': max_element (root);
                      printf ("\n");
                      break;

            case 'd': printf ("%d\n", diameter_tree(root));
                      break;

            case 's': printf ("%d\n", leftleaf_sum (root));
                      break;

            case 'e': exit(0);
                      break;
        }
    }
    return 0;
}