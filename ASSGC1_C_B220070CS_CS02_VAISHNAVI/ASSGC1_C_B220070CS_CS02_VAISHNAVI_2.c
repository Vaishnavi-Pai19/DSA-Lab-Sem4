//Vaishnavi B220070CS: Cycle 1 Part  - Question 2

#include <stdio.h>
#include <stdlib.h>

struct hash_node
{
    int value;
    struct hash_node* next;
};

typedef struct hash_node elem;

void initialize_hash (elem* arr[], int size)
{
    for (int i = 0; i<size; i++)
       arr[i] = NULL;
}

void insert_key (elem* hash_arr[], int key, int size)     //Function to insert a particular key in the hash table
{
    int index = key % size;

    elem* current = hash_arr[index];
    while (current != NULL)
    {
        if (current->value == key)
        {
            printf ("-1\n");
            return;
        }
        current = current->next;
    }

    current = hash_arr[index];
    elem* prev = NULL;
    while (current != NULL && current->value < key)
    {
        prev = current;
        current = current->next;
    }
    elem* new1 = (elem*)malloc(sizeof(elem));
    new1->value = key;
    new1->next = current;

    if (prev == NULL)
        hash_arr[index] = new1;
    else 
        prev->next = new1;
}

void search_key (elem* hash_arr[], int key, int size)       //Function to search for a particular key in the hash table
{
    int index = key % size;
    
    if (hash_arr[index] == NULL)
    {
       printf ("-1\n");
       return;
    }

    else if (hash_arr[index]->value == key)
    {
        printf ("%d 1\n", index);
        return;
    }

    else
    {
        elem* current = hash_arr[index];
        int count = 1;
        while (current != NULL)
        {
            if (current->value == key)
            {
                printf ("%d %d\n", index, count);
                return;
            }
            current = current->next;
            count++;
        }
           printf ("-1\n");
    }
} 


void delete_key (elem* hash_arr[], int key, int size)        //Function to delete a given key (if present) from the hash table
{
    int index = key % size;
    elem* current = hash_arr[index];
    elem* prev = NULL;

    if (current == NULL)
    {
        printf ("-1\n");
        return;
    }

    int count = 1;
    while (current != NULL && current->value != key)
    {
        prev = current;
        current = current->next;
        count++;
    }

    if (current == NULL)
    {
        printf ("-1\n");
        return;
    }

    if (prev == NULL)
       hash_arr[index] = current->next;
    else 
       prev->next = current->next;

    free(current);
    printf ("%d %d\n", index, count);
}

void print_index (elem* hash_table[], int index)         //Function to print all the elements present in a particular slot of the hash table
{
    if (hash_table[index] == NULL)
    {
        printf ("-1\n");
        return;
    }
    elem* now = hash_table[index];
    while (now != NULL)
    {
        printf ("%d ", now->value);
        now = now->next;
    }
    printf ("\n");
}

void update_key (elem* hash[], int old, int new, int size)    //Function to udpate a key
{
    int index = old % size;
    elem* now = hash[index];
    elem* prev = NULL;
    int count = 1;
    int found;

    while (now != NULL && now->value != old)
    {
        prev = now;
        now = now->next;
        count++;
    }

    if (now == NULL)
    {
        printf ("-1\n");
        return;
    }
    else  
       found = 1;

    int new_ind = new % size;
    now = hash[new_ind];
    while (now != NULL)
    {
        if (now->value == new)
        {
            printf ("-1\n");
            return;
        }
        now = now->next;
    }
    
    if (found)
    {
        delete_key (hash, old, size);
        insert_key (hash, new, size);
    }
    return;
}

int main()
{
    int table_size;
    scanf ("%d", &table_size);

    elem* hash_table[table_size];
    initialize_hash (hash_table, table_size);
    
    char choice;
    int key1, key2;
    while (1)
    {
        scanf (" %c", &choice);
        switch (choice)
        {
            case 'i': scanf ("%d", &key1);
                      insert_key (hash_table, key1, table_size);
                      break;

            case 'd': scanf ("%d", &key1);
                      delete_key (hash_table, key1, table_size);
                      break;

            case 'p': scanf ("%d", &key1);
                      print_index (hash_table, key1);
                      break;

            case 's': scanf ("%d", &key1);
                      search_key (hash_table, key1, table_size);
                      break;

            case 'u': scanf ("%d %d", &key1, &key2);
                      update_key (hash_table, key1, key2, table_size);
                      break;
            
            case 'e': exit(0);
                      break;
         }
    }
    return 0;
}