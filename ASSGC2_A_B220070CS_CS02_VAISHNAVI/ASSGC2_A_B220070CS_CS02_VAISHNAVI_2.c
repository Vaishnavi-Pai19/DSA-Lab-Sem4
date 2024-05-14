//Vaishnavi B220070CS: Cycle 2 Part A - Question 2

#include <stdio.h>
#include <stdlib.h>

struct avl_node
{
    int key;
    int value;
    struct avl_node* left;
    struct avl_node* right;
    int height;
};

typedef struct avl_node* node;

node create_new (int key, int value)
{
    node new = (node)malloc(sizeof(struct avl_node));
    new->key = key;
    new->value = value;
    new->left = NULL;
    new->right = NULL;
    new->height = 1;
    return new;
}

int max (int a, int b)
{   return (a > b) ? a : b;  }

int height (node p)
{
    return p == NULL ? 0 : p->height;
}

int bal_factor (node calc)
{
    if (calc == NULL)
       return 0;
    return height(calc->left) - height(calc->right);
}

node right_rotate (node y)
{
    node x = y->left;
    node temp = x->right;

    x->right = y;
    y->left = temp;

    y->height = 1 + max(height(x->left), height(x->right));
    x->height = 1 + max(height(x->left), height(x->right));
    return x;
}

node left_rotate (node x)
{
    node y = x->right;
    node temp = y->left;

    y->left = x;
    x->right = temp;

    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(x->left), height(x->right));
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

node insert_pair (node root, int key, int value)
{
    if (root == NULL)
       return create_new (key, value);

    if (key < root->key)
       root->left = insert_pair (root->left, key, value);
    else if (key > root->key)
       root->right = insert_pair (root->right, key, value);
    else
    {
        root->value = value;
        return root;
    }

    root->height = 1 + max (height(root->left), height(root->right));

    int balance = bal_factor (root);

    if (balance > 1)
    {
        if (key < root->left->key)
        {
            return right_rotate (root);        
        }
        else
        {
            return rotate_leftright (root);        
        }
    }

    if (balance < -1)
    {
        if (key > root->right->key)
        {
            return left_rotate (root);        
        } 
        else 
        {
            return rotate_rightleft (root); 
        }          
    }
    return root;
}

void lower_bound (node root, int key)
{
    node current = root;
    node result = NULL;

    while (current != NULL)
    {
        if (current->key >= key)
        {
            result = current;
            current = current->left;
        }
        else
            current = current->right;
    }

    if (result == NULL)
       printf ("-1\n");
    else
       printf ("%d %d\n", result->key, result->value);
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

int avl_size(node root)
{
    if (root == NULL)
       return 0;

    return 1 + avl_size(root->left) + avl_size(root->right);
}

void ascending_tree (node root)
{
    if (root == NULL)
       return;

    ascending_tree (root->left);
    printf ("%d ", root->key);
    ascending_tree (root->right);
} 

int empty_avltree (node root)
{
    if (root == NULL)
       return 1;
    return 0;
}

int main ()
{
    node root = NULL;
    node result = NULL;
    char select;
    int key;
    int value;
    while (1)
    {
        scanf (" %c", &select);
        switch (select)
        {
            case 'i': scanf ("%d %d", &key, &value);
                      root = insert_pair (root, key, value);
                      break;

            case 'l': scanf ("%d", &key);
                      lower_bound (root, key);
                      break;

            case 'f': scanf ("%d", &key);
                      result = avl_find (root, key);
                      if (result == NULL)
                        printf ("-1\n");
                      else
                        printf ("%d %d\n", result->key, result->value);
                      break;

            case 's': printf ("%d\n", avl_size(root));
                      break;

            case 'e': printf ("%d\n", empty_avltree(root));
                      break;

            case 'p': if (empty_avltree(root))
                        printf ("-1\n");
                      else
                      {
                        ascending_tree (root);
                        printf ("\n");
                      }
                      break;
            
            case 't': exit(0);
                      break;
        }
    }
    return 0;
}