#include <stdio.h>
#include <stdlib.h>


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
		t = s->arr[s->c-1];
		s->c = s->c - 1;
	}
	return t;

}



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
	int * b;
	int * f;
	int * p;
	int * s;
};


int tm;

graph * initGraph(int num) {
	graph * g = (graph *)malloc(sizeof(graph));
	g->v = num;
	g->e = 0;
	g->adj = (node **)malloc(num*sizeof(node *));

	g->b = (int *)malloc(num*sizeof(int));
	g->f = (int *)malloc(num*sizeof(int));
	g->p = (int *)malloc(num*sizeof(int));
	g->s = (int *)malloc(num*sizeof(int));


	int i=0;
	for(i=0;i<num;i++) {
		g->adj[i] = NULL;
		g->s[i] = 0;
		g->b[i] = 0;
		g->f[i] = 0;
		g->p[i] = -1;

	}

	return g;
}

void addEdge(graph * g, graph * gt, int u, int v) {
	node * n = (node *)malloc(sizeof(node));
	n->v = v;
	n->next = g->adj[u];
	g->adj[u] = n;

	g->e = g->e + 1;
	
	n = (node *)malloc(sizeof(node));
	n->v = u;
	n->next = gt->adj[v];
	gt->adj[v] = n;
	
	gt->e = gt->e + 1;
}

void printGraph(graph * g) {
	int ver = g->v;
	int i;
	node * ele;
	for(i=0;i<ver;i++) {
		printf("%d :: ", i);	
		ele = g->adj[i];
		while(ele !=NULL) {
			printf("%d --> ", ele->v);
			ele = ele->next;
		}
		printf("\n");
	}
}

void dfs(graph  *g, int s, stack *st){
	tm++;
	g->b[s] = tm;
	g->s[s] = 1;
	//printf("%d\t", s);

	node *current= g->adj[s];
	
	while(current !=  NULL){
		if(g->s[current->v] == 0){
			g->p[current->v] = s;
			dfs(g, current->v, st);
		}
		current = current->next;
	}

	g->f[s]= ++tm;
	g->s[s] = 2;
	
	push(st, s);
}


void scc(graph *g, graph *gt){
	tm = 0;
	int ver = g->v, i;
	stack *st1= initStack(100);
	stack *st2= initStack(100);


	for(i=0;i<ver;i++){
		if(g->s[i] == 0){
			dfs(g, i, st1);
		}
	}

	for(i=0;i<ver;i++) {
		printf("%d :: %d\t%d\t%d\t%d\n", i, g->p[i], g->b[i], g->f[i], g->s[i] );
	}
	
	int vert;	

	while(st1->c!=0){
		vert= pop(st1);
		if(gt->s[vert] == 0){
			dfs(gt, vert, st2);
		}
		printf("\n");
	}

	for(i=0;i<ver;i++) {
		printf("%d :: %d\t%d\t%d\t%d\n", i, gt->p[i], gt->b[i], gt->f[i], gt->s[i] );
	}
}



int main(){
	int ver = 8;
	graph *g, * gt;
	g = initGraph(ver);
	gt= initGraph(ver);
	
	addEdge(g, gt, 0, 1);
	addEdge(g, gt, 1, 2);
	addEdge(g, gt, 2, 3);
	addEdge(g, gt, 2, 5);
	addEdge(g, gt, 3, 2);
	addEdge(g, gt, 3, 4);
	addEdge(g, gt, 4, 4);
	addEdge(g, gt, 5, 4);
	addEdge(g, gt, 6, 5);
	addEdge(g, gt, 5, 6);
	addEdge(g, gt, 7, 6);
	addEdge(g, gt, 1, 6);
	addEdge(g, gt, 1, 7);
	addEdge(g, gt, 7, 0);


	printGraph(g);
	printf("\n\n");
	printGraph(gt);

	scc(g, gt);	
}