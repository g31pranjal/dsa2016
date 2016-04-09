#include <stdio.h>
#include <stdlib.h>

typedef struct Node node;

struct Node {
	int v;
	node* next;
};

typedef struct Graph graph;

struct Graph {
	int v;
	int e;
	node ** adj;
};

graph * initGraph(int num) {
	graph *g = (graph *)malloc(sizeof(graph));
	g->v = num;
	g->e = 0;
	g->adj = (node **)malloc(num*sizeof(node *));
	int i;
	for(i=0;i<num;i++) {
		g->adj[i] = NULL;
	}
	return g;
}

void addEdge(graph *g, int u, int v) {
	node *n = (node *)malloc(sizeof(node));
	n->v = v;
	n->next = g->adj[u];
	g->adj[u] = n;

	node *m = (node *)malloc(sizeof(node));
	m->v = u;
	m->next = g->adj[v];
	g->adj[v] = m;

	g->e = g->e + 1;
}

int main() {
	graph *g = initGraph(8);
	addEdge(g, 1, 2);
	addEdge(g, 3, 4);

	int i;
}