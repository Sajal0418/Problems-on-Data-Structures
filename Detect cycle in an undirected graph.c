#include<stdlib.h>
#include<stdio.h>

/*edge list structure for each edge */
typedef struct{
    unsigned int first;
    unsigned int second;
}edge;


unsigned int depthFS(int *visit, const edge *edges, unsigned int n, unsigned int order, unsigned int element, int previous) {
    visit[element] = 1;
    for(int p = 0; p < n; p++)
     {
        if(edges[p].first == element) 
        {
            if(visit[edges[p].second] == 0) 
            {
                if(depthFS(visit, edges, n, order, edges[p].second, element))
                {
                    return 1;
                }
            }
            else if(edges[p].second != previous) 
            {
                return 1;
            }
        }
    }
    return 0;
}


unsigned int cycle_finder(const edge *edges , unsigned int n, unsigned int order)
{
    int visit[100];
    for(int p = 0; p < 100; p++)
    {
        visit[p] = 0;
    }
    for(int p = 0; p < order; p++) 
    {
        if(visit[p] == 0) 
        {
            if(depthFS(visit, edges, n, order, p, -1)) 
            {
                return 1;
            }
                for(int q = 0; q < 100; q++) 
                {
                    visit[q] = 0;
                }
        }
    }
    return 0;
}
/* DO NOTE THAT THE GRAPH TRAVERSAL IN THIS QUESTION ALWAYS STARTS WITH NODE 0  so you need not take any input for starting node */
int main(void)
{
    unsigned int order;  /* number of vertices */
    unsigned int n; /* number of edges */
    scanf("%d", &n);
    scanf("%d", &order);
    edge *edges;
    unsigned int ans;
    edges = malloc(n*sizeof(edge));
    if(edges==NULL)
    {
        return 1;
    }
    for(int i=0;i<n;++i)
    {
        scanf("%d", &edges[i].first);
        scanf("%d", &edges[i].second);
    }
        
    ans= cycle_finder(edges, n, order);
    printf(ans? "cyclic":"acyclic");
    free(edges);
    return 0;

}
