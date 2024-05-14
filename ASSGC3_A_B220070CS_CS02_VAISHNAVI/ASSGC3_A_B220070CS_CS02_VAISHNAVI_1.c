//Vaishnavi B220070CS: Cycle 1 Part A - Question 1

#include <stdio.h>
#include <stdlib.h>

int dfs_visit (int n, int A[n+1][n+1], int u, int visited[])
{
    int ans = 1;
    visited[u] = 1;                            //To account for the 1 based indexing
    //printf ("%d ", u);
    for (int i = 1; i<=n && A[u][i] != -1; i++)
    {
        int vtx = A[u][i];
        if (visited[vtx] == 0)
           ans += dfs_visit (n, A, vtx, visited);
    }
    return ans;
}

int check_connected (int n, int A[n+1][n+1], int visited[], int arr[], int* k)
{
    int connected = 0;
    (*k) = 0;
    for (int i = 0; i<n+1; i++)
       visited[i] = 0;
    for (int u = 1; u<= n; u++)     //1 based indexing
    {
        if (visited[u] == 0)
        {
            connected++;
            arr[(*k)++] = dfs_visit (n, A, u, visited);
        }
    }
    return connected;
}

int find_bridges (int u, int parent, int n, int A[n+1][n+1], int disc[], int low[], int visited[], int* bridges, int* time)
{
    low[u] = disc[u] = (*time)++;
    visited[u] = 1;

    for (int v = 1; v <= n; v++)
    {
        if (A[u][v] == -1 || A[u][v] == parent)                                //Either reached end of list or trying to move to parent
           continue;
        
        int vtx = A[u][v];
        if (visited[vtx])                                                     //Checking if vertex has already been visited
           low[u] = (low[u] < disc[vtx]) ? low[u] : disc[vtx];

        else                                                                 //Vertex has not been visited yet
        {
            find_bridges (vtx, u, n, A, disc, low, visited, bridges, time);
            low[u] = (low[u] < low[vtx]) ? low[u] : low[vtx];

            if (low[vtx] > disc[u])
               (*bridges)++;
        }
    }
}

int num_bridges (int n, int A[n+1][n+1], int disc[], int low[], int visited[])
{
    int bridges = 0;
    int time = 1;
    for (int i = 0; i<n+1; i++)
       disc[i] = low[i] = visited[i] = 0;

    for (int u = 1; u<=n; u++)
    {
        if (disc[u] == 0)
           find_bridges (u, 0, n, A, disc, low, visited, &bridges, &time);
    }
    if (bridges == 0)
       return -1;
    return bridges;
}

int find_ap (int u, int p, int n, int A[n+1][n+1], int disc[], int low[], int ap_arr[], int* time)
{
    int children = 0;
    low[u] = disc[u] = ++(*time);

    for (int v = 1; v <= n; v++)
    {
        if (A[u][v] == -1 || A[u][v] == p)                                //Either reached end of list or trying to move to parent
           continue;
        
        int vtx = A[u][v];
        if (disc[vtx] == 0)     
        {
            children++;
            //printf ("Hi\n");
            find_ap (vtx, u, n, A, disc, low, ap_arr, time);
            if (low[vtx] >= disc[u])
               ap_arr[u] = 1;
            low[u] = (low[u] < low[vtx]) ? low[u] : low[vtx];
        }
        else                                                //Checking if vertex has already been visited
           low[u] = (low[u] < disc[vtx]) ? low[u] : disc[vtx];
    }
    //printf ("%d %d\n", children,u);
    return children;
}

int num_ap (int n, int A[n+1][n+1], int disc[], int low[])
{
    int points = 0;
    int time = 0;
    int ap_arr[n+1];
    for (int i = 0; i<n+1; i++)
       disc[i] = low[i] = ap_arr[i] = 0;

    for (int u = 1; u<=n; u++)
    {
            if (disc[u] == 0)
            {
                if (find_ap(u, u, n, A, disc, low, ap_arr, &time) > 1)
                    ap_arr[u] = 1;
                else
                    ap_arr[u] = 0;

            }
    }
    for (int i = 1;i <= n; i++)
    {
        if(ap_arr[i])
            points++;
    }
    if (points == 0)
       return -1;
    return points;
}

void sort (int n, int arr[], int k)
{
    int max;
    for (int i = 0; i<k; i++)
    {
        max = arr[i];
        int j = i+1;
        while (j<k)
        {
            if (arr[j] < max)
            {
                int temp;
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;

                max = arr[i];
            }
            j++;
        }
    }
}

int main ()
{
    int n;
    scanf ("%d", &n);
    int arr[n+1][n+1];

    for (int i = 0; i<=n; i++)
    {
        for (int j = 0; j<=n; j++)
        {
            arr[i][j] = -1;       //All initialized to -1
        }
    }
    
    int row;

    for (int i = 0; i<n; i++)
    {
        scanf ("%d", &row);
        int j = 1;
        int k;
        char c = getchar();
        if (c == '\n')
           continue;
        else
        {
            while (c != '\n')
            {
               scanf ("%d%c", &k, &c);
               arr[row][j] = k;
               j++;
            }
        }
    }
    int label[n+1];
    int disc[n+1];
    int low[n+1];

    int comp[n];
    for (int i = 0; i<n; i++)
       comp[i] = 0;
    int k = 0;

    char select;
    while (1)
    {
        scanf (" %c", &select);
        switch (select)
        {
            case 'n': printf ("%d\n", check_connected(n, arr, label, comp, &k));
                      break;
            
            case 's': check_connected(n, arr, label, comp, &k);
                    sort (n, comp, k);
                    for (int i = 0; i<k; i++)
                        printf ("%d ", comp[i]);
                    printf ("\n");
                    break;

            case 'b': printf ("%d\n", num_bridges(n, arr, disc, low, label));
                      break;

            case 'a': printf ("%d\n", num_ap(n, arr, disc, low));
                      break;

            case 't': exit(0);
        }
    }
    return 0;
}
