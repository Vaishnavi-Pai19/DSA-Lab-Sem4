//Vaishnavi B220070CS: Cycle 3 Part B - Question 4

//Floyd-Warshall algorithm to find all the distances in a weighted, undirected graph

#include <stdio.h>
#include <stdlib.h>

void floyd_warshall (int n, int A[n][n])
{
     for (int k = 0; k < n; k++) 
     {
        for (int i = 0; i < n; i++) 
        {
            for (int j = 0; j < n; j++) 
            {
                if (A[i][k] != 10000 && A[k][j] != 10000 && A[i][j] > A[i][k] + A[k][j]) {
                    A[i][j] = A[i][k] + A[k][j];
                }
            }
        }
    }

    for (int i = 0; i<n; i++)
    {
        for (int j = 0; j<n; j++)
           printf ("%d ", A[i][j]);
        printf ("\n");
    }
}

int main()
{
    int n;
    scanf ("%d", &n);
    int adj_mat[n][n];

    for (int u = 0; u<n; u++)
    {
        int k;
        for (int v = 0; v<n; v++)
        {
            scanf ("%d", &k);
            if (k == -1)
                adj_mat[u][v] = 10000;
            else 
               adj_mat[u][v] = k;
        }
    }

    floyd_warshall (n, adj_mat);
    return 0;
}