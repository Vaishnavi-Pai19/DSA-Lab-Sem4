//Vaishnavi B220070CS: Cycle 3 Part B - Question 3

//Dijkstra's Algorithm for finding shortest paths

#include <stdio.h>
#include <stdlib.h>

void dijkstra_algo (int V, int start, int list[V][V], int weights[V][V])
{
    int shortest[V], visited[V], prev[V];

    for (int i = 0; i<V; i++)
    {
       shortest[i] = 10000;
       visited[i] = 0;
       prev[i] = -1;
    }
    shortest[start] = 0;                       //Shortest path from a source node to itself is 0
    prev[start] = -1;                          //Source node does not have a previous node

    /*for (int j = 1; list[start][j] != -1; j++)
    {
        int vtx = list[start][j];
        if (visited[vtx] == 0)
        {
            if (weights[start][j] < shortest[vtx])
            {
                shortest[vtx] = weights[start][j];
                prev[vtx] = start;
            }
        }
    }*/

    while (1)
    {
        int min_dist = 10000;
        int min_vtx = -1;                        

        for (int v = 0; v < V ; v++)                          //Finding the minimum distance among all the adjacent nodes of the current node to begin checking from the next adjacent vertice
        {
            if (!visited[v] && shortest[v] < min_dist)
            {
                min_vtx = v;                                  //Min_vtx is the current node from which we are checking the adjacent nodes
                min_dist = shortest[v];                       //Min_dist is the distance that has been covered until the current node
            }
        }

        if (min_vtx == -1)                                    //If min_vtx remains -1, then all nodes have been visited
           break;

        visited[min_vtx] = 1;

        for (int j = 1; list[min_vtx][j] != -1; j++)          //Traversing through the adjacent nodes of the current node
        {
            int vtx = list[min_vtx][j];
            if (!visited[vtx] && weights[min_vtx][j] != -1)
            {
                int dist = min_dist + weights[min_vtx][j];    //New distance to the vtx is the min_dist + weight of the joining edge
                if (dist < shortest[vtx])                     //Update if the new distance is shorter than the previous shortest distance to vtx
                {
                    shortest[vtx] = dist;
                    prev[vtx] = min_vtx;
                }
            }
        }
    }

    for (int i = 0; i<V; i++)
        printf ("%d ", shortest[i]);
}

int main ()
{
    int V;
    scanf ("%d", &V);

    int adj[V][V];
    int weights[V][V];

    for (int i = 0; i<V; i++)
    {
        for (int j = 0; j<V; j++)
           adj[i][j] = -1, weights[i][j] = -1;
    }

    int row;
    for (int i = 0; i<V; i++)
    {
        scanf ("%d", &row);
        int j = 1;
        int k;
        char c = getchar();
        while (c != '\n')
        {
            scanf ("%d%c", &k, &c);
            adj[row-1][j] = k-1;                    //To account for the code's 0-based indexing
            j++;
        }
    }

    for (int i = 0; i<V; i++)
    {
        scanf ("%d", &row);
        int j = 1;
        int k;
        char c = getchar();
        while (c != '\n')
        {
            scanf ("%d%c", &k, &c);
            weights[row-1][j] = k;
            j++;
        }
    }

    int src;
    scanf ("%d", &src);

    dijkstra_algo (V, src-1, adj, weights);
    return 0;
}