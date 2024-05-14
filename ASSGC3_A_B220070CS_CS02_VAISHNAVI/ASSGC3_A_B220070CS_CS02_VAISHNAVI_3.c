//Vaishnavi B220070CS: Cycle 3 Part A - Question 3

#include <stdio.h>
#include <stdlib.h>

int check_cycle (int v, int visited[], int parent, int n, int A[n][n])
{
    visited[v] = 1;
    for (int i = 0; i < n; i++)
    {
        if (A[v][i])
        {
            if (i == parent)
               continue;
            if (visited[i])
               return 1;
            if (check_cycle(i, visited, v, n, A))
               return 1;
        }
    }
    return 0;
}

void dfs (int v, int visited[], int n, int A[n][n])
{
    visited[v] = 1;
    for (int i = 0; i < n; i++)
    {
        if (A[v][i] && !visited[i])
           dfs (i, visited, n, A);
    }
}

int valid_tree (int n, int A[n][n])
{
    //Checking if it is undirected at first
    for (int u = 0; u < n; u++)
    {
        for (int v = 0; v < n; v++)
        {
            if (A[u][v] != A[v][u])
               return -1;
            else
               continue;
        }
    }

    //Checking if it is connected
    int visited[n];
    for (int i = 0; i < n; i++)
       visited[i] = 0;
    
    int comp = 0;
    for (int u = 0; u < n; u++)
    {
        if (!visited[u])
        {
            dfs(u, visited, n, A);
            comp++;
        }
    }

    if (comp > 1)
       return -1;

    //Checking if it is acyclic
    for (int i = 0; i < n; i++)
       visited[i] = 0;

    for (int u = 0; u < n; u++)
    {
        if (!visited[u])
        {
            if (check_cycle(u, visited, -1, n, A))
               return -1;
        }
    }

    return 1;
}

void print (int path[], int length)
{
    for (int i = 0; i < length; i++)
       printf ("%d ", path[i]);
    printf ("\n");
}

void print_paths (int src, int dest, int visited[], int n, int A[n][n], int path[], int len)
{
    visited[src] = 1;
    path[len++] = src;

    if (src == dest)
       print (path, len);
    else
    {
        for (int i = 0; i<n; i++)
        {
            if (A[src][i] && !visited[i])
            {
                print_paths(i, dest, visited, n, A, path, len);
                visited[i] = 0;
            }

        }

        visited[src] = 0;
    }
}

int main ()
{
    int n;
    scanf ("%d", &n);
    int adj[n][n];

    for (int i = 0; i<n; i++)
    {
        for (int j = 0; j<n; j++)
        {
            adj[i][j] = 0;       //All initialized to -1
        }
    }
    
    int row;
    for (int i = 0; i<n; i++)
    {
        scanf ("%d", &row);
        int k;
        char c = getchar();
        if (c == '\n')
           continue;
        else
        {
            while (c != '\n')
            {
               scanf ("%d%c", &k, &c);
               if (k != -1)
                  adj[row][k] = 1;
            }
        }
    }

    /*printf ("Hi\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf ("%d ", adj[i][j]);
        }
        printf ("\n");
    }*/
    
    int src, dest;
    char choice;
    int i, len = 0;
    int visited[n];
    int path[n];
    while (1)
    {
        scanf (" %c", &choice);
        switch (choice)
        {
            case 't': printf ("%d\n", valid_tree(n, adj));
                      break;
            
            case 'a': scanf ("%d %d", &src, &dest);
                      for (i = 0; i < n; i++)
                        visited[i] = 0;
                      print_paths (src, dest, visited, n, adj, path, len);
                      break;
            
            case 'x': exit(0);
        }
    }
    return 1;
}