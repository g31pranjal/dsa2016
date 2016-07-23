#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct Graph graph;

struct Graph {
	int v;
	int e;
	int c;
	int **adj;
};

graph * initGraph(int num) {
	int i,j;
	graph * g = (graph *)malloc(sizeof(graph));
	g->v = num;
	g->e = 0;
	g->adj = (int **)malloc(num*sizeof(int *));
	for(i=0;i<num;i++) {
		g->adj[i] = (int *)malloc(num*sizeof(int));
		for(j=0;j<num;j++) {
			g-adj[i][j] = 0;
		}
	}
	
	return g;
}

void addEdge(graph * g, int u, int v) {
	g->adj[u][v] = 1;
	g->adj[v][u] = 1;

	g->e = g->e + 1;
}	


int main() {
	int tc;
	scanf("%d", &tc);

	graph **g = (graph **)malloc(tc*sizeof(graph *));
	graph *ng; 

	int i, v, e, m, n, c, s, j;

	for(i=0;i<tc;i++) {
		scanf("%d %d", &v, &e);
		ng = initGraph(v);

		for(j=0;j<e;j++) {
			scanf("%d %d %d", &m, &n, &c);
			addEdge(ng, m-1, n-1, w);

		}

		scanf("%d", &s);
		ng->crab = c;
		g[i] = ng;

	}

	for(i=0;i<tc;i++) {
		crabbing(g[i]);
	}

	return 0;

}