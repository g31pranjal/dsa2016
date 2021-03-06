#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct Node node;

struct Node {
	int v;
	int wt;
	node * next;
};

typedef struct Graph graph;

struct Graph {
	int v;
	int e;
	node ** adj;
	int start;
};

graph * initGraph(int num) {
	graph * g = (graph *)malloc(sizeof(graph));
	g->v = num;
	g->e = 0;
	g->adj = (node **)malloc(num*sizeof(node *));
	g->start = 0;

	int i=0;
	for(i=0;i<num;i++) {
		g->adj[i] = NULL;
	}

	return g;
}

void addEdge(graph * g, int u, int v, int wt) {
	node * n = (node *)malloc(sizeof(node));
	n->v = v;
	n->wt = wt;
	n->next = g->adj[u];
	g->adj[u] = n;

	node * n1 = (node *)malloc(sizeof(node));
	n1->v = u;
	n1->wt = wt;
	n1->next = g->adj[v];
	g->adj[v] = n1;

	g->e = g->e + 1;
}	

int startDJK(graph *g) {
	int str = g->start;
	int ver = g->v;

	int cloud[ver];
	int dist[ver];

	int func = 1, min, mini, i, j;


	for(i=0;i<ver;i++) {
		cloud[i] = -1;
		dist[i] = -1;
	}

	dist[str] = 0;
	node * ele;

	min = 0;
	mini = str;

	while(func != 0) {
		for(j=mini+1;j<ver;j++) {
			if(cloud[j] == -1 && dist[j] >= 0 && min >= dist[j]) {
				min = dist[j];
				mini = j;
			}
		}
		cloud[mini] = 0;
		ele = g->adj[mini];	
		while(ele != NULL) {
			if(cloud[ele->v] == -1) {
				if(dist[ele->v] == -1 || dist[ele->v] > min + ele->wt) {
					dist[ele->v] = min + ele->wt;
				}
			}
			ele = ele->next;
		}

		func = 0;
		min = mini = -1;
		for(j=0;j<ver;j++) {
			if(cloud[j] == -1 && dist[j] >= 0) {
				min = dist[j];
				mini = j;
				func = 1;
				break;
			}
		}
	}

	return 0;
}


int main() {
	int tc;
	scanf("%d", &tc);

	graph **g = (graph **)malloc(tc*sizeof(graph *));
	graph *ng; 

	int i, v, e, m, n, w, s, j;

	for(i=0;i<tc;i++) {
		scanf("%d %d", &v, &e);
		ng = initGraph(v);

		for(j=0;j<e;j++) {
			scanf("%d %d %d", &m, &n, &w);
			addEdge(ng, m-1, n-1, w);

		}

		scanf("%d", &s);
		ng->start = s-1;
		g[i] = ng;

	}

	for(i=0;i<tc;i++) {
		startDJK(g[i]);
	}

	return 0;

}