//Vaishnavi B220070CS: Cycle 1 Part B - Question 3

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct binary_node {
    int key;
    struct binary_node *left, *right;
};

typedef struct binary_node* node;

node create_new (int key)
{
    node new = (node)malloc(sizeof(struct binary_node));
    new->key = key;
    new->left = NULL;
    new->right = NULL;
    return new;
}

node bstfromstring (char* str, int* index)                 //Function to form the binary search tree from the given string representation
{
    int num = 0;

    while (str[*index] >= '0' && str[*index] <= '9')          //To account for the multi-digit numbers
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
            root->left = bstfromstring (str, index);
        while (str[*index] != ')')
           (*index)++;
        (*index)++;
    }

    if (str[*index] == '(')
    {
        (*index)++;
        if (str[*index] != ')')
           root->right = bstfromstring (str, index);
        while (str[*index] != ')')
           (*index)++;
        (*index)++;
    }
    return root;
}

void print_range (node tree, int k1, int k2)                      //PrintRangeValues(T,k1,k2)
{
    if (tree == NULL)
       return;
    if (k1 < tree->key)
       print_range (tree->left, k1, k2);
    if (k1 <= tree->key && k2 >= tree->key)
       printf ("%d ", tree->key);
    if (k2 > tree->key)
       print_range (tree->right, k1, k2);
}

int ancestors (node root, int value)            //Ancestors(T,k)
{
    if (root == NULL)
       return 0;
    if (root->key == value)
    {
        printf ("%d ", root->key);
        return 1;
    }

    if (ancestors(root->left, value) || ancestors(root->right, value))
    {
        printf ("%d ", root->key);
        return 1;
    }
    return 0;
}

int main()
{
    char string[1000];
    fgets (string, sizeof(string), stdin);

    int len = strlen(string);
    if (len>0 && string[len-1] == '\n')
    {  string[len-1] = '\0';  }

    int index = 0;
    node root = bstfromstring (string, &index);

    char choice;

    while (1)
    {
        scanf (" %c", &choice);
        switch (choice)
        {
            case 'p': int start, end;
                      scanf ("%d %d", &start, &end);
                      print_range (root, start, end);
                      printf ("\n");
                      break;

            case 'a': int target;
                      scanf ("%d", &target);
                      ancestors (root, target);
                      printf ("\n");
                      break;

            case 'e': exit(0);
                      break;         
        }
    }
   return 0;
}