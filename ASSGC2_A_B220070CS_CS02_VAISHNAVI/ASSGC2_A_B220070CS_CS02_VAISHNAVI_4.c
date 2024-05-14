//Vaishnavi B220070CS: Cycle 2 Part A - Question 4

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct rb_node 
{
    int key;
    char colour;
    struct rb_node* left;
    struct rb_node* right;
};

typedef struct rb_node* node;

node create_node (int key, char colour)
{
    node new = (node)malloc(sizeof(struct rb_node));
    new->key = key;
    new->colour = colour;
    new->left = NULL;
    new->right = NULL;
    return new;
}

node build_rbtree (char* str, int* index)
{
    if (str[*index] == '(')
    {
        (*index) += 2;                 //Skipping the ( and the white space after it
        if (str[*index] == ')')
        {
            (*index) += 2;
            return NULL;
        }
        
        int key = 0;                                    //To get the keys that are multi-digit integers 
        while (str[*index] >= '0' && str[*index] <= '9')
        {
            key *= 10;
            key += (str[*index] - '0');
            (*index)++;
        }
        (*index) ++;                 //Moving past the white space after the integer
        char rb = str[*index];
        (*index) += 2;             //Skipping the colour character and white space after it

        node root = create_node (key, rb);

        root->left = build_rbtree (str, index);
        root->right = build_rbtree (str, index);
        (*index) += 2;
        
        return root;
    }
    return NULL;
}

void inorder_traverse (node root)
{
    if (root == NULL)
       return;

    inorder_traverse (root->left);
    printf ("%d ", root->key);
    inorder_traverse (root->right);
}

int black_height (node root, int current, int* result)
{
    if (root == NULL)
    {
        if (*result == -1)
           *result = current;
        else if (*result != current)
           return 0;
        return 1;
    }

    if (root->colour == 'B')
       current++;

    return black_height (root->left, current, result) && black_height (root->right, current, result);
}

int consecutive_red (node root)
{
    if (root == NULL)
       return 1;

    if (root->colour == 'R' && ((root->left != NULL && root->left->colour == 'R') || (root->right != NULL && root->right->colour == 'R')))
       return 0;
    
    if (!consecutive_red(root->left) || !consecutive_red(root->right))
       return 0;

    return 1;
}

int check_rbtree (node root)
{
    if (root == NULL)       //An empty tree is a red-black tree
       return 1;
    
    if (root->colour != 'B' && root->colour != 'R')      //Property 1: Every node is either red or black
       return 0;

    if (root->colour != 'B')       //Property 2: Root node is always black
       return 0;

    if (!consecutive_red(root))           //Property 4: If a node is red, both its children should be blac, i.e. no two consecutive red nodes
       return 0;
    
    int result = -1;
    if (!black_height (root, 0, &result))    //Property 5: Black height of every node is always same
       return 0;

    return 1;
}

int main ()
{
    char parenthesis[10000];
    fgets (parenthesis, sizeof(parenthesis), stdin);

    int len = strlen (parenthesis);
    parenthesis[len-1] = '\0';
    
    int index = 0;
    node root = NULL;
    root = build_rbtree (parenthesis, &index);
    //inorder_traverse (root);
    //printf ("\n");
    int check = check_rbtree (root);
    printf ("%d\n", check);
    return 0;
}
