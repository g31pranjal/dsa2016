#include<stdio.h>
#include<stdlib.h>

typedef struct Node node;

struct Node{
	int v;
	struct Node *next;
};

typedef struct Graph graph;

struct Graph{
	int n;
	int m;
	node ** adjList;
};

typedef struct Edge edge;

struct Edge{
	int v;
	int u;
	struct Edge *next;
};

edge *createEdge(int u, int v){
	edge *newEdge= (edge*)malloc(sizeof(edge));
	newEdge->v= v;
	newEdge->u= u;
	newEdge->next= NULL;
	return newEdge;
}


edge * push(edge *s, int u, int v){
	edge *newEdge= createEdge(u, v);
	newEdge->next= s;
	s= newEdge;
	return s;
}

int isEmpty(edge *s){
	if(s== NULL)
		return 1;
	return 0;
}

edge* pop(edge *s){
	if(isEmpty(s))
		return NULL;
	edge *e= s;
	s= s->next;
	free(e);
	return s;
}

int time;
edge* s;

node *createNode(int v){
	node *newNode= (node*)malloc(sizeof(node));
	newNode->v= v;
	newNode->next= 	NULL;
	return newNode;
}

graph *createGraph(int n){
	graph *g= (graph*)malloc(sizeof(graph));
	g->n=n;
	g->m=0;
	g->adjList= (node**)malloc(n*sizeof(node*));
	int i;
	for(i=0;i<n;i++){
		g->adjList[i]= NULL;
	}
	return g;
	
}

void addEdge(graph *g, int v, int u){
	node *newNode= createNode(v);
	newNode->next= g->adjList[u];
	g->adjList[u]= newNode;

	newNode= createNode(u);
	newNode->next= g->adjList[v];
	g->adjList[v]= newNode;
	
	g->m++;
}

void outputComponent(int u, int v){
	int a, b;
	//printf("%d, %d \n", u, v);
	//printStack();

	do{	
		if(s!= NULL){
			a=s->u;
			b=s->v;
			printf("%d-%d\t", a,b);
			s= pop(s);
		}
	}while(!(a==u && b==v));
	printf("\n");
}

void printStack(){
	edge *curr= s;
	while(curr!= NULL){
		printf("%d%d\t", curr->u, curr->v);
curr= curr->next;
}
}


void DFSvisit(int u, int *visited, int *parent, int *low, int *d, graph *g){
	visited[u]=1;
	time++;
	d[u]= time;
	low[u]= d[u];
	node *current= g->adjList[u];
	int v;
	while(current!= NULL){
		v= current->v;
		if(visited[v]==0){	
			s= push(s, u, v);
			parent[v]=u;
			DFSvisit(v, visited, parent, low, d, g);
			if(low[v]>= d[u]){
				outputComponent(u,v);
			}
			low[u]= low[u]<low[v]?low[u]: low[v];
		}
		else if(parent[u]!= v && (d[v]<d[u])){
			s= push(s, u, v);
			low[u]= low[u]<d[v]?low[u]:d[v];
		}
		current= current->next;
	}
}

void biconnectedComponents(graph *g){
	time=0;
	s= NULL;
	int *visited= (int*)malloc(g->n*sizeof(int));
	int *parent= (int*)malloc(g->n*sizeof(int));
	int *low= (int*)malloc(g->n*sizeof(int));
	int *d= (int*)malloc(g->n*sizeof(int));
	int i;

	for(i=0;i<g->n;i++){
		visited[i]=0;
		parent[i]=-1;
		low[i]=-1;
		d[i]=-1;
	}

	for(i=0;i<g->n;i++){
		if(visited[i]==0)
			DFSvisit(i, visited, parent, low, d, g);
	}
}

int main(){
	graph *g= createGraph(8);
	addEdge(g, 0,1);
	addEdge(g, 0,2);
	addEdge(g, 0,3);
	addEdge(g, 1,2);
	addEdge(g, 1,3);
	addEdge(g, 1,4);
	addEdge(g, 2,3);
	addEdge(g, 3,4);
	addEdge(g, 3,5);
	addEdge(g, 5,4);
	addEdge(g, 6,4);
	addEdge(g, 6,7);

	biconnectedComponents(g);

	
}