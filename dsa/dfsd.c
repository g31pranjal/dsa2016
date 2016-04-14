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

	int q = 0;
	int *tm;
	tm = &q;

	printf("%x", tm);

	p[source] = -1;
	
	for(i=0;i<ver;i++) {
		if(s[i] == 0)
			dfsvisit(g, i, p, b, f, s, tm);
	}

	for(i=0;i<ver;i++) {
		printf("%d\t%d\t%d\t%d\n", p[i], b[i], f[i], s[i]);
	}

}

void dfsvisit(graph * g, int source, int * p, int * b , int * f , int *s, int *tm) {
	printf("%x\n", tm);

	 *tm = *tm + 1;
	b[source] = *tm;
	s[source] = 1;

	node * ele;
	int t;
	ele = g->adj[source];

	while(ele != NULL) {
		t = ele->v;

		if(s[t] == 0) {
			// discovery edge
			p[t] = source;
			labelEdge(g, source, t, 'd');
			dfsvisit(g, t, p, b, f, s, tm);
		}
		else if(b[t] < b[source] && s[t] == 1) {
			//backward edge
			labelEdge(g, source, t, 'b');
		}
		else if(b[t] > b[source] && s[t] == 2 && f[t] > b[t]) {
			// forward edge
			labelEdge(g, source, t, 'f');		
		}
		else {
			// cross edge 
			labelEdge(g, source, t, 'c');
		}
		ele = ele->next;
	}
	*tm = *tm + 1;
	f[source] = *tm;
	s[source] = 2;
}




int main() {
	int ver = 8;
	graph *g;
	g = initGraph(ver);

	addEdge(g, 0, 7);
	addEdge(g, 0, 4);
	addEdge(g, 1, 3);
	addEdge(g, 1, 2);
	addEdge(g, 2, 1);
	addEdge(g, 2, 3);
	addEdge(g, 3, 0);
	addEdge(g, 3, 4);
	addEdge(g, 4, 5);
	addEdge(g, 5, 7);
	addEdge(g, 6, 5);
	addEdge(g, 7, 6);
	addEdge(g, 7, 4);

	printGraph(g);

	dfsinit(g, 2);

	printGraph(g);




}