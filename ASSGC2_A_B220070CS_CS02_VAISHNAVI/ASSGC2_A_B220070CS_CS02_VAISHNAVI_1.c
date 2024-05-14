//Vaishnavi B220070CS: Cycle 2 Part A - Question 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct avl_node 
{
    int key;
    struct avl_node* left;
    struct avl_node* right;
    int height;
};

typedef struct avl_node* node;

int height (node p)
{
    return p == NULL ? 0 : p->height;
}

void update_h (node up)
{
    int max = height(up->left) > height(up->right) ? height(up->left) : height(up->right);
    up->height = 1 + max;
}

int bal_factor (node calc)
{
    if (calc == NULL)
       return 0;
    return height(calc->left) - height(calc->right);
}

node create_new (int k)
{
    node new = (node)malloc(sizeof(struct avl_node));
    new->key = k;
    new->left = NULL;
    new->right = NULL;
    new->height = 1;
    return new;
}

node right_rotate (node y)
{
    node x = y->left;
    node temp = x->right;

    x->right = y;
    y->left = temp;

    update_h (y);
    update_h (x);
    return x;
}

node left_rotate (node x)
{
    node y = x->right;
    node temp = y->left;

    y->left = x;
    x->right = temp;

    update_h (x);
    update_h (y);
    return y;
}

node rotate_leftright (node p)
{
    p->left = left_rotate (p->left);
    return right_rotate (p);
}

node rotate_rightleft (node p)
{
    p->right = right_rotate (p->right);
    return left_rotate (p);
}

node insert_key (node root, int key, int* left_rot, int* right_rot)
{
    if (root == NULL)
        return create_new (key);
       
    if (key < root->key)
       root->left = insert_key (root->left, key, left_rot, right_rot);
    else if (key > root->key)
       root->right = insert_key (root->right, key, left_rot, right_rot);
    else 
    {
        //*left_rot = 0;
        //*right_rot = 0;
        return root;
    }   
    
    update_h (root);
    int balance = bal_factor (root);

    if (balance > 1)
    {
        if (key < root->left->key)
        {
            *right_rot += 1;
            return right_rotate (root);        
        }
        else
        {
            *left_rot += 1;
            *right_rot += 1;
            return rotate_leftright (root);        
        }
    }

    if (balance < -1)
    {
        if (key > root->right->key)
        {
            *left_rot += 1;
            return left_rotate (root);        
        } 
        else 
        {
            *right_rot += 1;
            *left_rot += 1;
            return rotate_rightleft (root); 
        }
                    
    }
    return root;
}

node avl_find (node root, int key)
{
    if (root == NULL)
       return NULL;
    
    if (root->key == key)
       return root;

    if (key < root->key)
       return avl_find (root->left, key);
    else 
       return avl_find (root->right, key);
}

void avl_find_print (node root, int key)
{
    node found = avl_find (root, key);
    if (found == NULL)
    {
        printf ("-1\n");
        return;
    }
    while (root != NULL && root->key != key)
    {
        printf ("%d ", root->key);
        if (key < root->key)
           root = root->left;
        else 
           root = root->right;
    }
    printf ("%d\n", key);
}

void preorder_traverse (node root)
{
    if (root == NULL)
       return;

    printf ("%d ", root->key);
    preorder_traverse (root->left);
    preorder_traverse (root->right);
}

int main ()
{
    node root = NULL;
    char select;
    int value;
    int left = 0;
    int right = 0;
    while (1)
    {
        scanf (" %c", &select);
        switch (select)
        {
            case 'i': scanf ("%d", &value);
                      root = insert_key (root, value, &left, &right);
                      break;

            case 'x': scanf ("%d", &value);
                      avl_find_print (root, value);
                      break;

            case 'p': preorder_traverse (root);
                      printf ("\n");
                      break;

            case 's': //avl_calc (root, value, &left, &right);
                      printf ("%d %d\n", left, right);
                      break;

            case 'e': exit(0);
                      break;
        }
    }
    return 0;
}