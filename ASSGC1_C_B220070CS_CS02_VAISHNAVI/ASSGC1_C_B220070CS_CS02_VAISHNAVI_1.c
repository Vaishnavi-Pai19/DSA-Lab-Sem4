//Vaishnavi B220070CS: Cycle 1 Part  - Question 1

#include <stdio.h>
#include <stdlib.h>

void insert_element (int* arr, int value, int size)
{
    int index = value % size;
    int i = 1;
    while (i < size && arr[index] != -1)           //Open addressing to insert elements in case of collisions
    {
        index = (index + 1) % size;
        i++;
    }
    arr[index] = value;
}

int search_key (int* arr, int key, int size)
{
    int index = key % size;
    int original = index;
    while (arr[index] != key)
    {
        index = (index + 1) % size;
        if (arr[index] == -1 || index == original)    //Which means the open addressing index CAN contain another element, but if it is empty then the key does not exist at all since otherwise it would have been in the first slot
           return 0;
    }
    return 1;
}

void initialize_table (int* arr, int size)
{
    for (int i = 0; i<size; i++)
       arr[i] = -1;
}

void union_sets (int size, int* arr, int m, int n, int* A, int* B)     //Union(A,B)
{
    for (int i = 0; i < m; i++)
    {
        if (search_key(arr, A[i], size))
           continue;
        else
        {
            insert_element (arr, A[i], size);
            printf ("%d ", A[i]);
        } 
    }
    for (int j = 0; j < n; j++)
    {
        if (search_key(arr, B[j], size))
           continue;
        else
        {
            insert_element (arr, B[j], size);
            printf ("%d ", B[j]);
        } 
    }
    initialize_table (arr, size);
}

int duplicate (int* arr, int index, int value)       //Function to check for duplicates in a particular array
{
    int found = 0;
    for (int i = index-1; i>=0; i--)
    {
        if (arr[i] == value)
           found++;
    }
    if (found)
       return 1;
    else 
       return 0;
}

void intersection_sets (int size, int* arr, int m, int n, int* A, int* B)      //Intersection(A,B)
{
    int exist = 0;
    for (int j = 0; j < n; j++)
    {
        if (!search_key(arr, B[j], size))
            insert_element (arr, B[j], size);
    } 
    for (int i = 0; i < m; i++)
    {
        if (duplicate(A, i, A[i]))
           continue;
        else
        {
            if (search_key(arr, A[i], size))
            {
                printf ("%d ", A[i]);
                exist++;
            }   
        }
    }
    if (exist == 0)
       printf ("-1");
    initialize_table (arr, size);
}

void set_difference (int size, int* arr, int m, int n, int* A, int* B)        //SetDifference(A,B)
{
    int exist = 0;
    for (int j = 0; j < n; j++)
    {
        if (!search_key(arr, B[j], size))
            insert_element (arr, B[j], size);
    } 
    for (int i = 0; i < m; i++)
    {
        if (duplicate(A, i, A[i]))
           continue;
        else
        {
            if (!search_key(arr, A[i], size))
            {
                printf ("%d ", A[i]);
                exist++;
            }   
        }
    }
    if (exist == 0)
       printf ("-1");
    initialize_table (arr, size);
}

int main ()
{
    int m_size, n_size;
    scanf ("%d", &m_size);
    scanf ("%d", &n_size);
    int A[m_size];
    int B[n_size];
    for (int i = 0; i < m_size; i++)
    {
        scanf ("%d", &A[i]);
    }
    for (int j = 0; j < n_size; j++)
    {
        scanf ("%d", &B[j]);
    }

    int max = (m_size > n_size) ? m_size : n_size;    //Size of the hash table = 2 * max(m,n)
    int size = 2*max;
    int hash_arr[size];
    initialize_table (hash_arr, size);
    
    char select;
    char first, second;
    while (1)
    {
        scanf (" %c", &select);
        switch (select)
        {
            case 'u': scanf (" %c", &first);
                      scanf (" %c", &second);
                      if (first == 'A')
                         union_sets (size, hash_arr, m_size, n_size, A, B);
                      else 
                         union_sets (size, hash_arr, n_size, m_size, B, A);
                      printf ("\n");
                      break;
            
            case 'i': scanf (" %c", &first);
                      scanf (" %c", &second);
                      if (first == 'A')
                         intersection_sets (size, hash_arr, m_size, n_size, A, B);
                      else 
                         intersection_sets (size, hash_arr, n_size, m_size, B, A);
                      printf ("\n");
                      break;

            case 's': scanf (" %c", &first);
                      scanf (" %c", &second);
                      if (first == 'A')
                         set_difference (size, hash_arr, m_size, n_size, A, B);
                      else 
                         set_difference (size, hash_arr, n_size, m_size, B, A);
                      printf ("\n");
                      break;
                
            case 'e': exit(0);
                      break;
        }
    }
    return 0;
}