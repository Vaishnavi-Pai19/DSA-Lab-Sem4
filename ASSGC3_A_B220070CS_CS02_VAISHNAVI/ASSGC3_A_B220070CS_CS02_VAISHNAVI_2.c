//Vaishnavi B220070CS: Cycle 3 Part A - Question 2

#include <stdio.h>
#include <stdlib.h>

struct arr_queue 
{
    int rear;
    int front;
    int* array;
};

struct arr_stack
{
    int top;
    int* array;
};

typedef struct arr_queue* queue;
typedef struct arr_stack* stack;

int empty_queue (queue Q)
{
    if (Q->front == -1)
       return 1;
    return 0;
}

void enqueue (queue Q, int Vtx)
{
    if (empty_queue(Q))            //Queue is empty
    {
        Q->front = 0;
        Q->rear = 0;
    }
    else
    {
        Q->rear++;
    }
    Q->array[Q->rear]  = Vtx;
}

void dequeue (queue Q)
{
    if (empty_queue(Q)==-1)         
    {
        printf ("-1\n");
    }
    else
    {
        //printf ("%d", Q->array[Q->front]);
        if (Q->rear == Q->front)
           Q->rear = Q->front = -1;
        else 
           Q->front++;
    }
}

//Kahn's Algorithm to detect if the graph is acyclic
//A topological sort is possible in a directed graph only if the graph is also acyclic,
//so by checking if it is acyclic we can say if the topological sort will be possible
int detect_cycle (int n, int A[n][n])
{
    int indegree[n];
    queue Q = (queue)malloc(sizeof(struct arr_queue));
    Q->rear = Q->front = -1;
    Q->array = (int*)malloc(sizeof(int) * n);
    int count = 0;

    for (int i = 0; i<n; i++)
       indegree[i] = 0;
    
    for (int u = 0; u < n; u++)
    {
        for (int v = 0; v < n; v++)
        {
            if (A[u][v] == 1)
               indegree[v]++;
        }
    }

    /*for (int i = 0; i<n; i++)
       printf ("%d ", indegree[i]);
    printf ("\n");*/

    for (int u = 0; u < n; u++)
    {
        if (indegree[u] == 0)
           enqueue (Q, u);            //Vertices are 1 based
    }

    while (!empty_queue(Q))
    {
        int u = Q->array[Q->front];
        dequeue(Q);
        count++;

        for (int v = 0; v < n; v++)
        {
            if (A[u][v] == 1)
            {
                indegree[v]--;
                if (indegree[v] == 0)
                   enqueue(Q, v);
            }  
        }
    }
    
    if (count == n)
       return 1;
    else 
       return -1;
}

int empty_stack (stack S)
{
    return S->top == -1;
}

void push (stack S, int Vtx)
{
    S->array[++(S->top)] = Vtx;
}

int pop (stack S)
{
    if (empty_stack(S))
    {
        printf ("Error\n");
        return -1;
    }
    return S->array[(S->top)--];
}

void dfs_visit (int n, int A[n][n], int u, int label[], stack S)
{
    label[u] = 1;
    for (int v = 0; v<n; v++)
    {
        if (A[u][v] == 1 && label[v] == 0)
           dfs_visit (n, A, v, label, S);
    }
    push (S, u);
}

void dfs_transpose (int n, int transpose[n][n], int u, int label[])
{
    label[u] = 1;
    for (int v = 0; v < n; v++)
    {
        if (transpose[u][v] == 1 && label[v] == 0)
           dfs_transpose(n, transpose, v, label);
    }
}

//Kosarajo's algorithm for finding the number of connected components
int num_connected (int n, int A[n][n])
{
    if (detect_cycle(n, A) == 1)
       return n;
    else
    {    
        int visited[n];
        stack S = (stack)malloc(sizeof(struct arr_stack));
        S->top = -1;
        S->array = (int*)malloc(sizeof(int)*n);

        for (int i = 0; i<n; i++)
           visited[i] = 0;
        for (int u = 0; u<n; u++)
        {
           if (visited[u] == 0)
              dfs_visit (n, A, u, visited, S);
        }

        int transpose[n][n];
        for (int i = 0; i<n; i++)
        {
            for (int j = 0; j<n; j++)
               transpose[j][i] = A[i][j];
        }

        for (int i = 0; i<n; i++)
           visited[i] = 0;

        int count = 0;

        while (!empty_stack(S))
        {
            int u = pop(S);
            if (visited[u] == 0)
            {
                dfs_transpose(n, transpose, u, visited);
                count++;
            }
        }
        return count;
    }
}

int main ()
{
    int n;
    scanf("%d", &n);
    int A[n][n];
    for (int i = 0; i < n; i++)
    {
        int k;
        for (int j = 0; j < n; j++)
        {
            scanf ("%d", &k);
            A[i][j] = k;
        }
    }

    /*printf ("Start of table\n");
    for (int i = 0; i<n; i++)
    {
        for (int j = 0; j<n; j++)
           printf ("%d ", A[i][j]);
        printf ("\n");
    }
    printf ("End of table\n");*/

    char choice;
    while (1)
    {
        scanf (" %c", &choice);
        switch (choice)
        {
            case 't': printf ("%d\n", detect_cycle(n, A));
                      break;

            case 'c': printf ("%d\n", num_connected(n, A));
                      break;

            case 'x': exit(0);
        }
    }
    return 0;
}