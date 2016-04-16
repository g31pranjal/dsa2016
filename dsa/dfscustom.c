// dfs : customized for undirected


#include <stdlib.h>
#include <stdio.h>

typedef struct Node node;

struct Node {
	int v;
	char type;
	node * next;
};

typedef struct Graph graph;

struct Graph {
	int v;
	int e;
	node ** adj;
	int * b;
	int * p;
	int * f;
	int * s;
};

graph * initGraph(int num) {
	graph * g = (graph *)malloc(sizeof(graph));
	g->v = num;
	g->e = 0;
	g->adj = (node **)malloc(num*sizeof(node *));
	g->b = (int *)malloc(num*sizeof(int));
	g->p = (int *)malloc(num*sizeof(int));
	g->f = (int *)malloc(num*sizeof(int));
	g->s = (int *)malloc(num*sizeof(int));


	int i=0;
	for(i=0;i<num;i++) {
		g->adj[i] = NULL;
		g->b[i] = -1;
		g->f[i] = -1;
		g->p[i] = -1;
		g->s[i] = 0;

	}

	return g;
}

void addEdge(graph * g, int u, int v) {
	node * n = (node *)malloc(sizeof(node));
	n->v = v;
	n->type = 'u';
	n->next = g->adj[u];
	g->adj[u] = n;

	g->e = g->e + 1;
}

void deleteEdge(graph * g, int u, int v) {
	node * ele = g->adj[u];
	node * prev = NULL;

	while(ele != NULL) {
		if(ele->v != v) {
			prev = ele;
			ele = ele->next;
		}
		else {
			if(prev != NULL) {
				prev->next = ele->next;
			}
			else {
				g->adj[u] = ele->next;
			}
			free(ele);
			g->e = g->e - 1;
			break;
		}
	}
}

void labelEdge(graph * g, int u, int v, char label) {
	node * ele = g->adj[u];
	while(ele != NULL) {
		if(ele->v == v) {
			ele->type = label;
		}
		ele = ele->next;
	}
}

void printGraph(graph * g) {
	int ver = g->v;
	int i;
	node * ele;
	for(i=0;i<ver;i++) {
		printf("%d :: ", i);	
		ele = g->adj[i];
		while(ele !=NULL) {
			printf("%d, %c -->", ele->v, ele->type);
			ele = ele->next;
		}
		printf("\n");
	}
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
		s->c = n;
		s->c = s->c + 1;
	}
}

int pop(stack * s) {
	int t;
	if(s->c != 0) {
		t = s->arr[s->c];
		s->c = s->c - 1;
	}
	return t;

}


void dfsinit(graph *g, int source) {
	int ver = g->v;

	int i=0, t, l;
	node * ele;

	int q = 0;
	int *tm;
	tm = &q;

	g->p[source] = -1;
	
	dfsvisit(g, source, tm);

	for(i=0;i<ver;i++) {
		printf("%d\t%d\t%d\t%d\n", g->p[i], g->b[i], g->f[i], g->s[i]);
	}

}

void dfsvisit(graph * g, int source, int *tm) {
	printf("%x\n", tm);

	 *tm = *tm + 1;
	g->b[source] = *tm;
	g->s[source] = 1;

	node * ele;
	int t;
	ele = g->adj[source];

	while(ele != NULL) {
		t = ele->v;

		if(g->s[t] == 0) {
			g->p[t] = source;
			deleteEdge(g, t, source);
			labelEdge(g, source, t, 'd');
			dfsvisit(g, t, tm);
		}
		else if( g->p[source] != t && g->b[t] < g->b[source]) {
			labelEdge(g, source, t, 'b');
			deleteEdge(g, t, source);
		}
		ele = ele->next;
	}
	*tm = *tm + 1;
	g->f[source] = *tm;
	g->s[source] = 2;
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

	printGraph(g);

	dfsinit(g, 4);

	printGraph(g);




}