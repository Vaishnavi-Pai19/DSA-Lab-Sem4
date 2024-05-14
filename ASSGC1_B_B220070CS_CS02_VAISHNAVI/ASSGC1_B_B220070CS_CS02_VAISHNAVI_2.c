//Vaishnavi B220070CS: Cycle 1 Part B - Question 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct binary_node {
    int key;
    struct binary_node *left, *right;
};

typedef struct binary_node* node;

struct queue_list {
    node data[100];
    int front;
    int rear;
};

typedef struct queue_list* queue;

node create_new (int key)
{
    node new = (node)malloc(sizeof(struct binary_node));
    if (new == NULL)
       exit(0);
    new->key = key;
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

node treefromstring (char* str, int* index)
{
    int num = 0;

    while (str[*index] >= '0' && str[*index] <= '9')
    {
        num *= 10;
        num += (str[*index] - '0');
        (*index)++;
    }

    node root = create_new (num);
    //printf ("%d ", root->key);

    if (str[*index] == '(')
    {
        (*index)++;
        if (str[*index] != ')')
            root->left = treefromstring (str, index);
        while (str[*index] != ')')
           (*index)++;
        (*index)++;
    }

    if (str[*index] == '(')
    {
        (*index)++;
        if (str[*index] != ')')
           root->right = treefromstring (str, index);
        while (str[*index] != ')')
           (*index)++;
        (*index)++;
    }
    return root;
}

void level_order (node root)                  //LevelOrderTraversal(T)
{
    if (root == NULL)
        return;
    
    queue Q = (queue)malloc(sizeof(struct queue_list));
    Q->front = -1;
    Q->rear = -1;

    enqueue (Q, root);

    while (empty_check(Q) == 0)
    {
        node temp = dequeue (Q);
        printf ("%d ", temp->key);
        if (temp->left != NULL)  
           enqueue (Q, temp->left);
        if (temp->right != NULL)
           enqueue (Q, temp->right);
    }
   
    free(Q);
}

void inorder_traverse (node root, int* arr, int* count)            //Function to store elements of a subtree in an array in its irorder form
{
    if (root == NULL)
       return;

    inorder_traverse (root->left, arr, count);
    arr[(*count)++] = root->key;
    inorder_traverse (root->right, arr, count);
}

int bst_sum (node root)               //Recursive function to find the sum of a BST
{
    if (root == NULL)
       return 0;
    return root->key + bst_sum(root->left) + bst_sum(root->right);
}

int check_bst (node root)                //Function to check if a subtree is a BST based on if the inorder traversal is sorted
{
    int arr[1000];
    int count = 0;
    inorder_traverse (root, arr, &count);

    for (int i = 0; i<count-1; i++)
    {
        if (arr[i] >= arr[i+1])
           return 0;
    }
    return bst_sum(root);
}

int maximum_bstsum (node root)              //MaximumSumBST(T)        
{
    if (root == NULL)
       return 0;
    
    int max_sum = 0;
    if (check_bst(root))
    {
        int sum = bst_sum(root);
        if (sum > max_sum)
           max_sum = sum;
    }

    int left_max = maximum_bstsum(root->left);
    int right_max = maximum_bstsum(root->right);

    if (left_max > max_sum)
       max_sum = left_max;
    if (right_max > max_sum)
       max_sum = right_max;
    
    return max_sum;
}

void right_view (node root, int *prev_level, int curr_level)           //RightView(T)
{
    if (root == NULL)
      return;

    if (*prev_level < curr_level)
    {
        printf ("%d ", root->key);
        *prev_level = curr_level;
    }
    curr_level++;

    right_view (root->right, prev_level, curr_level);
    right_view (root->left, prev_level, curr_level);
    return;
}


int main()
{
    char string[1000];
    fgets (string, sizeof(string), stdin);

    int len = strlen(string);
    if (len>0 && string[len-1] == '\n')
    {  string[len-1] = '\0';  }

    int index = 0;
    node root = treefromstring (string, &index);

    char select;
    while (1)
    {
        scanf (" %c", &select);
        switch (select)
        {
            case 'l': level_order (root);
                      printf ("\n");
                      break;
            
            case 'm': printf ("%d\n", maximum_bstsum(root));
                      break;

            case 'r':  int curr = 1;
                       int prev = 0;
                       right_view (root, &prev, curr);
                       printf ("\n");
                       break;
                
            case 'e': exit(0);
                      break;
        }
    }
    return 0;
}