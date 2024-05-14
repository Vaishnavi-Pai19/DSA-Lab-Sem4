//Vaishnavi B220070CS: Cycle 1 Part - Question 4

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int hash_function (int key, int n)
{
    return key % n;
}

void initialize_table (int* arr, int size)
{
    for (int i = 0; i<size; i++)
       arr[i] = -1;
}

int check_prime (int num)
{
    if (num <= 1)
       return 0;
    if (num <= 3)
       return 1;

    for (int i = 2; i*i <= num; i++)
       if (num % i == 0)
          return 0;
    return 1;
}

int max_prime (int number)
{
    for (int i = number - 1; i>= 2; i--)
       if (check_prime(i))
          return i;
    return 2;
}

void linear_probing_insert (int keys[], int hash_arr[], int n, int size)    //h′(k) = (h(k) + i) % m, i = 1,2....
{
    int collisions = 0;
    for (int i = 0; i < n; i++)
    {
        int index = hash_function (keys[i], size);

        int j = 1;
        while (j < size && hash_arr[index] != -1)
        {
            index = (index + 1) % size;
            collisions++;
            j++;
        }
        hash_arr[index] = keys[i];
        printf ("%d ", index);
    }
    printf ("\n%d\n", collisions);
    initialize_table(hash_arr, size);
}

void quadratic_probing_insert (int keys[], int hash_arr[], int n, int size)    //h′(k) = (h(k) + i^2) % m, i = 1,2...
{
    int collisions = 0;
    for (int i = 0; i < n; i++)
    {
        int index = hash_function (keys[i], size);
        int original = index;

        int j = 1;
        while (hash_arr[index] != -1)
        {
            index = (original + j*j) % size;
            collisions++;
            j++;
        }
        hash_arr[index] = keys[i];
        printf ("%d ", index);
    }
    printf ("\n%d\n", collisions);
    initialize_table(hash_arr, size);
}

void double_hashing_insert (int keys[], int hash_arr[], int n, int size)    //h1(k) = k mod N,  h2(k) = R − (key mod R), h'(k) = (h1(key) + i*h2(key)) % N, i = 0,1,2....
{
    int prime = max_prime (size);
    //printf ("%d\n", prime);
    
    int collide = 0;
    for (int i = 0; i < n; i++)
    {
        int h1_index = hash_function (keys[i], size);
        int h2_index = prime - (keys[i] % prime);

        int index = h1_index;
        int j = 0;

        if (hash_arr[index] == -1)
        {
            hash_arr[index] = keys[i];
            printf ("%d ", index);
        }
           
        else 
        {
            int j = 1;
            while(hash_arr[index] != -1)
            {
                index = (h1_index + (j * h2_index)) % size;
                collide++;
                j++;
            }
            hash_arr[index] = keys[i];
            printf ("%d ", index);
        }
    }
    printf ("\n%d\n", collide);
    initialize_table(hash_arr, size);
}

int main()
{
    int size;
    scanf ("%d", &size);
    getchar();

    int hash_table[size];
    initialize_table (hash_table, size);
    
    char keys_string[1000];
    fgets(keys_string, sizeof(keys_string), stdin);

    int len = strlen(keys_string);
    if (len>0 && keys_string[len-1] == '\n')
    {  keys_string[len-1] = '\0';  }

    int count = 0;
    for (int i = 0; keys_string[i] != '\0'; i++)
    {
        if (keys_string[i] == ' ')
           count++;
    }

    int keys[count + 1];
    int num, j = 0, k = 0;
    
    while (keys_string[j] != '\0')
    {
        num = 0;
        while (keys_string[j] != ' ' && keys_string[j] != '\0')
        {
            num *= 10;
            num += (keys_string[j] - '0');
            j++;
        }
        keys[k++] = num;
        if (keys_string[j] == ' ')
           j++;
    }

    linear_probing_insert (keys, hash_table, count + 1, size);
    quadratic_probing_insert (keys, hash_table, count + 1, size);
    double_hashing_insert (keys, hash_table, count + 1, size);
    return 0;
}