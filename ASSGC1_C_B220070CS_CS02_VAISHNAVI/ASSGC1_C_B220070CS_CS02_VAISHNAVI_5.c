//Vaishnavi B220070CS: Cycle 1 Part - Question 5

#include <stdio.h>
#include <stdlib.h>

void count_distinct (int arr[], int N, int K)
{
    if (K > N)
       exit(0);

    int hash_map[100000] = {0};   //Stores count of elements in current window
    int count = 0;                //Stores count of distinct elements in the current window
    for (int i = 0; i < K; i++)
    {
        if (hash_map[arr[i]] == 0)
           count++;
        hash_map[arr[i]] += 1;
    }

    printf ("%d ", count);

    for (int i = K; i < N; i++)
    {
        if (hash_map[arr[i-K]] == 1)
           count--;
        hash_map[arr[i-K]] -= 1;

        if (hash_map[arr[i]] == 0)
           count++;
        hash_map[arr[i]] += 1;

        printf ("%d ", count);
    }
}

int main ()
{
    int length, size;
    scanf ("%d", &length);
    int arr[length];
    scanf ("%d", &size);
    for (int i = 0; i < length; i++)
    {
        scanf ("%d", &arr[i]);
    }
    count_distinct (arr, length, size);
    return 0;
}