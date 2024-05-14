//Vaishnavi B220070CS: Cycle 3 Part B - Question 1

//Finding Minimum Spanning Tree using Prim's Algorithm
//for undirected weighted graphs

#include <stdio.h>
#include <stdlib.h>

void mst_weight (int V, int parent[V], int A[V][V])
{
    int total = 0;
    for (int i = 1; i < V; i++)                     //Since starting node is considered to be 0, parent[0] should be excluded
        total += A[i][parent[i]];
    printf ("%d\n", total);
}

void prim_mst (int V, int A[V][V], int start, int parent[V], int choice)
{
    int key[V];                                    //To pick the minimum weighted edge
    int mst_vertices[V];                           //To keep track of vertices includes in the MST

    for (int i = 0; i < V; i++)
    {
        key[i] = 10000;
        mst_vertices[i] = 0;
    }
    
    key[start] = 0;                                //Making the starting node 0 so that it is picked first
    parent[start] = -1;                            //Parent[] stores the constructed MST; starting node does not have any parent so -1

    for (int i = 0; i < V; i++)
    {
        int min = 10000;
        int min_index = -1;

        for (int j = 0; j < V; j++)
        {
            if (mst_vertices[j] == 0 && key[j] < min)         //If unvisited and having key < min, it becomes the next node
            {
                min = key[j];
                min_index = j;
            }
        }

        mst_vertices[min_index] = 1;                          //Marking it as visited

        if (choice == 0 && parent[min_index] != -1)           //If choice is 0, it means it has to print the sequence of edges
        {
           printf ("%d %d ", parent[min_index], min_index);   //u = parent[min_index], v = min_index
           if (i == V-1)
              printf ("\n");
        }

        for (int k = 0; k < V; k++)
        {
            if (A[min_index][k] && mst_vertices[k] == 0 && A[min_index][k] < key[k])   //Checks for adjacent nodes and if they are univisited
            {
                parent[k] = min_index;             //If distance to k is lesser than k's current key, parent is updated
                key[k] = A[min_index][k];          //Key value of k is updated and it is now the min. weighted edge to connect k to MST
            }
        }
    }
    if (choice == 1)                               //If choice is 1, it means it has to find the total weight of the MST
       mst_weight (V, parent, A);
    else 
       return;
}



int main ()
{
    int V;
    scanf ("%d", &V);
    int adj[V][V];
    for (int i = 0; i < V; i++)
    {
        int k;
        for (int j = 0; j < V; j++)
        {
            scanf ("%d", &k);
            adj[i][j] = k;
        }
    }

    int start;
    scanf ("%d", &start);
    int parent[V];
    
    char select;
    while (1)
    {
        scanf (" %c", &select);
        switch (select)
        {
            case 's': getchar();
                      scanf ("%d", &start);
                      getchar();
                      prim_mst (V, adj, start, parent, 0);
                      break;

            case 't': prim_mst (V, adj, 0, parent, 1);          //Weight of all MSTs are the same, no matter starting node
                      break;

            case 'x': exit (0);
        }
    }
    return 0;
}