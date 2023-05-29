#include <stdio.h>
#include <stdlib.h>
#define MAX_NODES 50
#define INFINITY 9999

typedef struct graph
{
    int n;                         /* Number of vertices in graph */
    int adj[MAX_NODES][MAX_NODES]; /* Adjacency matrix */
} Graph;

// creates the graph
void create_graph(Graph *adj_mat)
{

    int i, j;
    for (int i = 0; i < adj_mat->n; ++i)
    {
        for (int j = 0; j < adj_mat->n; ++j)
        {
            adj_mat->adj[i][j] = 0;
        }
    }
    while (1)
    {
        // edge between two vertex
        scanf("%d %d\n", &i, &j);
        if (i < 0 && j <= 0 || i >= adj_mat->n || j >= adj_mat->n)
        {
            break;
        }
        adj_mat->adj[i][j] = 1;
    }
}
// helper functions for inserting an element into a queue
void append(int *queue, int v, int *pqr)
{
    ++(*pqr);
    queue[*pqr] = v;
}
// helper function to delete from a queue
int delete (int *queue, int *pqr)
{
    int res = queue[0];
    for (int i = 0; i < *pqr; ++i)
    {
        queue[i] = queue[i + 1];
    }
    --(*pqr);
    return res;
}

void breadth_search(Graph *adj_mat, int src, int des, int *prev)
{
    int queue[adj_mat->n];
    for (int p = 0; p < (adj_mat->n); p++)
    //initialising queue
        queue[p] = 0;
    int front = 0, rear = -1;

    int visited[adj_mat->n];
    for (int p = 0; p < (adj_mat->n); p++)
        visited[p] = -99;

    queue[++rear] = src;
    //making the visited of source to 1
    visited[src] = 1;

    int x, i;
    while (front <= rear)
    {
        x = queue[front++];
        for (int p = 0; p < (adj_mat->n); p++)
        {
            if ((adj_mat->adj)[x][p] && (visited[p] == -99))
            {
                queue[++rear] = p;
                visited[p] = 1;
                prev[p] = x;
            }
        }
    }
}

// bfs function to calculate the minimum distance
// You are required to complete this function
int find_dist(Graph *adj_mat, int src, int des)
{

    int prev[adj_mat->n];
    for (int p = 0; p < (adj_mat->n); p++)
        prev[p] = -99;

    breadth_search(adj_mat, src, des, prev);

    int path[(adj_mat->n)];
    int var = 0;
    for (int p = des; p != -99; p = prev[p])
        path[var++] = p;

    int tp;
    for (int p = 0; p < var / 2; p++)
    {
        tp = path[p];
        path[p] = path[var - p - 1];
        path[var - p - 1] = tp;
    }

    if (path[0] == src)
        return var - 1;

    return -1;
}

int main()
{
    Graph adj_mat;

    int source, dest;

    // number of vertex
    scanf("%d\n", &adj_mat.n);
    // creates adj matrix
    create_graph(&adj_mat);

    // source vertex
    scanf("%d\n", &source);

    // destination vertex
    scanf("%d", &dest);

    int result = find_dist(&adj_mat, source, dest);
    printf("%d", result);
    return 0;
}
