#include <stdlib.h>
#include <stdio.h>

typedef struct Node node;

struct Node {
	int v;
	node * next;
};

typedef struct Graph graph;

struct Graph {
	int v;
	int e;
	node ** adj;
};

graph * initGraph(int num) {
	graph * g = (graph *)malloc(sizeof(graph));
	g->v = num;
	g->e = 0;
	g->adj = (node **)malloc(num*sizeof(node *));

	int i=0;
	for(i=0;i<num;i++) {
		g->adj[i] = NULL;
	}

	return g;
}

void addEdge(graph * g, int u, int v) {
	node * n = (node *)malloc(sizeof(node));
	n->v = v;
	n->next = g->adj[u];
	g->adj[u] = n;

	g->e = g->e + 1;
}


typedef struct Q q;

struct Q {
	int * arr;
	int front;
	int rear;
	int max;
};

q * initQ(int num) {
	q * a = (q *)malloc(sizeof(q));
	a->arr = (int *)malloc(num*sizeof(int));
	a->max = num;
	a->front = 0;
	a->rear = 0;

	return a;
}

void enQ(q * q, int num) {
	if(q->rear != q->max - 1) {
		q->arr[q->rear] = num;
		q->rear++;
	}
}

int deQ(q * q) {
	int t;
	if(q->rear > q->front) {
		t = q->arr[q->front];
		q->front++;
	}
	return t;
}

void bfsinit(graph *g, int source) {
	int ver = g->v;

	int p[ver];
	int d[ver];
	int s[ver];

	int i=0, t, l;
	node * ele;

	for(i=0;i<ver;i++) {
		p[i] = -1;
		d[i] = -1;
		s[i] = 0;
	}

	p[source] = -1;
	d[source] = 0;
	s[source] = 1;

	q * q = initQ(100);

	enQ(q, source);

	while(q->rear != q->front) {
		t = deQ(q);
		ele = g->adj[t];
		while(ele != NULL) {
			l = ele->v;
			if(s[l] == 0) {
				p[l] = t;
				d[l] = d[t] + 1;
				s[l] = 1;
				enQ(q, l);
			}
			ele = ele->next;
		}
		s[t] = 2;
	}

	for(i=0;i<ver;i++) {
		printf("%d\t%d\t%d\n", p[i], d[i], s[i]);
	}

}




int main() {
	int ver = 8;
	graph *g;
	g = initGraph(ver);

	addEdge(g, 0, 1);
	addEdge(g, 1, 0);
	addEdge(g, 0, 3);
	addEdge(g, 3, 0);
	addEdge(g, 0, 4);
	addEdge(g, 4, 0);
	
	addEdge(g, 1, 2);
	addEdge(g, 2, 1);
	addEdge(g, 2, 3);
	addEdge(g, 3, 2);
	addEdge(g, 3, 4);
	addEdge(g, 4, 3);

	addEdge(g, 4, 5);
	addEdge(g, 5, 4);
	addEdge(g, 2, 7);
	addEdge(g, 7, 2);

	addEdge(g, 5, 7);
	addEdge(g, 7, 5);
	addEdge(g, 6, 7);
	addEdge(g, 7, 6);
	addEdge(g, 5, 6);
	addEdge(g, 6, 5);

	addEdge(g, 4, 6);
	addEdge(g, 6, 4);

	bfsinit(g, 4);


}