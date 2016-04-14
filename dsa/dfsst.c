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


typedef struct Stack stack;

struct Stack {
	int * arr;
	int c;
	int max;
};

stack * initStack(int max) {
	stack * s = (stack *)malloc(sizeof(stack));
	s->c = 0;
	s->max = max;
	s->arr = (int *)malloc(max*sizeof(int));

	return s;
}

void push(stack *s, int n) {
	if(s->c < s->max - 1) {
		s->arr[s->c] = n;
		s->c = s->c + 1;
	}
}

int pop(stack * s) {
	int t;
	if(s->c != 0) {
		t = s->arr[s->c - 1];
		s->c = s->c - 1;
	}
	return t;

}


void dfsinit(graph *g, int source) {
	int ver = g->v;

	int p[ver];
	int b[ver];
	int f[ver];
	int s[ver];

	int i=0, t, l;
	node * ele;

	for(i=0;i<ver;i++) {
		p[i] = -1;
		b[i] = -1;
		f[i] = -1;
		s[i] = 0;
	}

	stack * st = initStack(100);
	int tm = 0;
	p[source] = -1;
	tm = 1;
	push(st, source);

	while(st->c != 0) {
		t = pop(st);

		//printf("t : %d, ", t);

		s[t] = 2;
		b[t] = tm++;
		ele = g->adj[t];
		while(ele != NULL) {
			l = ele->v;
			if(s[l] == 0) {
				p[l] = t;
				push(st, l);
			}
			ele = ele->next;
		}

	}
	

	for(i=0;i<ver;i++) {
		printf("%d\t%d\t%d\t%d\n", p[i], b[i], f[i], s[i]);
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

	dfsinit(g, 4);




}