//Vaishnavi B220070CS: Cycle 3 Part B - Question 2

//Kruskal's algorithm for finding the minimum cost of spanning tree
//in a weighted undirected graph

#include <stdio.h>
#include <stdlib.h>

void swap_edges (int edges[][3], int i, int j)
{
    int temp[3];
    for (int k = 0; k<3; k++)
    {
        temp[k] = edges[i][k];
        edges[i][k] = edges[j][k];
        edges[j][k] = temp[k];
    }
}

void sort_edges (int num, int edges[num][3])
{
    for (int i = 0; i< num-1; i++)
    {
        for (int j = 0; j<num-i-1; j++)
        {
            if (edges[j][2] > edges[j+1][2])
               swap_edges(edges, j, j+1);
        }
    }
}

void make_set (int prnt[], int rnk[], int n)
{
    for (int i = 0; i<n; i++)
    {
        prnt[i] = i;
        rnk[i] = 0;
    }
}

int parent_find (int parent[], int node)
{
    if (parent[node] == node)
       return node;

    return parent[node] = parent_find (parent, parent[node]);
    
}

void union_set (int root_u, int root_v, int parent[], int rank[])
{
    root_u = parent_find(parent, root_u);
    root_v = parent_find(parent, root_v);

    if (rank[root_u] < rank[root_v])
       parent[root_u]  = root_v;
    else if (rank[root_u] > rank[root_v])
       parent[root_v] = root_u;
    else                                               //If ranks of both the roots are equal, root_u is chosen as the main root and its rank is incremented
    {
        parent[root_v] = root_u;
        rank[root_u]++;
    }
}

int kruskal_algo (int V, int num, int all_edges[num][3])
{
    sort_edges (num, all_edges);
    
    /*printf ("Table of all edges\n");
    for (int i = 0; i<num; i++)
    {
        for (int j = 0; j<3; j++)
           printf ("%d ", all_edges[i][j]);
        printf ("\n");
    }*/

    int size = num/2;
    int edges[size][3];
    for (int i = 0, j = 0; i<size, j<num; i++, j+=2)      //To get only the unique edges instead of both u->v and v->u
    {
        edges[i][0] = all_edges[j][0];
        edges[i][1] = all_edges[j][1];
        edges[i][2] = all_edges[j][2];
    }

    /*printf ("New table of edges\n");
    for (int i = 0; i<size; i++)
    {
        for (int j = 0; j<3; j++)
           printf ("%d ", edges[i][j]);
        printf ("\n");
    }*/

    int parent[V];
    int rank[V];

    make_set (parent, rank, V);
    int sum = 0;

    for (int i = 0; i<size; i++)
    {
        int u = parent_find (parent, edges[i][0]);
        int v = parent_find (parent, edges[i][1]);
        
        if (u != v)
        {
            union_set (u, v, parent, rank);
            sum += edges[i][2];
        }
    }
    printf ("%d\n", sum);
}

int main ()
{
    int n;
    scanf ("%d", &n);
    int adj_list [n][n];

    for (int u = 0; u<n; u++)
    {
        for (int v = 0; v<n; v++)
           adj_list[u][v] = -1;
    }

    int row;
    int num = 0;                        //Counter for number of edges
    for (int i = 0; i<n; i++)
    {
        scanf ("%d", &row);
        int j = 1;
        int k;
        char c = getchar();
        while (c != '\n')
        {
            scanf ("%d%c", &k, &c);
            adj_list[row][j] = k;
            j++;
            num++;
        }
    }

    /*for (int i = 0; i<n; i++)
    {
        for (int j = 0; j<n; j++)
           printf ("%d ", adj_list[i][j]);
        printf ("\n");
    }
    printf ("%d", count);*/
    
    int edges[num][3];
    int i = 0;                    //To keep track of the edge count
    for (int u = 0; u<n && i<num; u++)
    {
        scanf ("%d", &row);
        int j = 1;                //To keep track of the number of adjacent nodes to each vertex
        int k;                    //To keep track of the weights
        char c = getchar();
        while (c != '\n')
        {
            edges[i][0] = row;
            edges[i][1] = adj_list[row][j];
            scanf ("%d%c", &k, &c);
            edges[i][2] = k;
            j++;
            i++;
        }
    }

    /*for (int i = 0; i<num; i++)
    {
        for (int j = 0; j<3; j++)
           printf ("%d ", edges[i][j]);
        printf ("\n");
    }*/

    kruskal_algo (n, num, edges);
    return 0;
}