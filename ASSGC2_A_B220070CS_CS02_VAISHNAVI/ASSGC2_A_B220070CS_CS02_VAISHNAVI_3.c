//Vaishnavi B220070CS: Cycle 2 Part A - Question 3

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct redblack_node 
{
    int key;
    char colour;
    struct redblack_node* left;
    struct redblack_node* right;
    struct redblack_node* p;
};

typedef struct redblack_node* node;

void print_parenthesis (node root, node og)
{
    if (root == NULL)
    {
        printf ("()");
        return;
    }
      
    printf ("(%d%c", root->key, root->colour);
    print_parenthesis (root->left, og);
    printf ("");
    print_parenthesis (root->right, og);

    if ((root->left != NULL && root->right != NULL) && root != og)       //If we are not considering the root node, we need to move on the next subtree and print only a space
        {  printf ("");  }

    if (root->left == NULL || root->right == NULL) 
        {  printf (")");  }

    else if (root->left != NULL && root->right != NULL && root == og)      //If we are considering subtrees of root node, there shouldn't be a space after the last bracket
        {  printf (")");  }
}

node right_rotate (node y)
{
    node x = y->left;
    node temp = x->right;

    x->right = y;
    y->left = temp;

    //update_h (y);
    //update_h (x);
    return x;
}

node left_rotate (node x)
{
    node y = x->right;
    node temp = y->left;

    y->left = x;
    x->right = temp;

    //update_h (x);
    //update_h (y);
    return y;
}

node RB_insert_fixup (node* root, node z)
{
    while (z->p != NULL && z->p->colour == 'R')
    {
        if (z->p == z->p->p->left)
        {
            node uncle = z->p->p->right;
            if (uncle != NULL && uncle->colour == 'R')
            {
                z->p->colour = 'B';
                uncle->colour = 'B';
                z->p->p->colour = 'R';
                z = z->p->p;
            }
            else
            {
                if (z == z->p->right)
                {
                    z = z->p;
                    if (z == *root)
                       *root = left_rotate (z);
                    else
                       z->p = left_rotate (z);
                }
                z->p->colour = 'B';
                z->p->p->colour = 'R';
                node gp = z->p->p;
                if (gp == *root)
                    *root = right_rotate (gp);
                else
                    z->p->p = right_rotate (gp);
            }
        }
        else                                            //if (z->p == z->p->p->right)
        {
            node uncle = z->p->p->left;
            if (uncle != NULL && uncle->colour == 'R')
            {
                z->p->colour = 'B';
                uncle->colour = 'B';
                z->p->p->colour = 'R';
                z = z->p->p;
            }
            else
            {
                if (z == z->p->left)
                {
                    z = z->p;
                    if (z == *root)
                       *root = right_rotate (z);
                    else
                       z->p = right_rotate (z);
                }
                z->p->colour = 'B';
                z->p->p->colour = 'R';
                node gp = z->p->p;
                if (gp == *root)
                    *root = left_rotate (gp);
                else
                    z->p = left_rotate (gp);
            }
        }
    }
    (*root)->colour = 'B';
    return *root;
}

void RB_insert (node* root, int key)
{
    node new_node = (node)malloc(sizeof(struct redblack_node));
    new_node->key = key;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->colour = 'R';

    node parent = NULL;
    node current = *root;

    while (current != NULL)
    {
        parent = current;
        if (key < current->key)
           current = current->left;
        else  
           current = current->right;
    }
    new_node->p = parent;

    if (parent == NULL)
       *root = new_node;
    else if (key < parent->key)
       parent->left = new_node;
    else  
       parent->right = new_node;

    *root = RB_insert_fixup(root, new_node);
    print_parenthesis (*root, *root);
    printf ("\n");
}

int main ()
{
    node root = NULL;
    char choice[10];
    int num = 0;

    while (1)
    {
        fgets (choice, sizeof(choice), stdin);
        num = 0;

        if (choice[0] == 'e')
        {
            exit (0);
            return 0;
        }

        int i = 0;
        while (choice[i] != '\n' && choice[i] != '\0')
        {
            if (choice[i] >= '0' && choice[i] <= '9')
            {
                num *= 10;
                num += choice[i] - '0';
            }
            else
                num = 0;
            i++;
        }

        if (num > 0)
           RB_insert (&root, num);
    }
    /*RB_insert (&root, 15);
    RB_insert (&root, 8);*/
    return 0;
}
