#include<stdio.h>
#include<stdlib.h>

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
};

typedef struct HeapNode hnode;

struct HeapNode{
	int v;
	int d;
};

int heapsz;

int parent(int i){
	return (i-1)/2;
}

int left(int i){
	return 2*i+1;
}

int right(int i){
	return 2*i+2;
}

void swap(hnode heap[], int i1, int i2){
	hnode h1= heap[i1];
	heap[i1]= heap[i2];
	heap[i2]= h1;
}

hnode extractMin(hnode heap[]){
	hnode min= heap[0];
	heap[0]= heap[heapsz-1];
	minHeapify(heap, 0);
	heapsz--;
	return min;
}

void decreaseKeyInHeap(hnode * heap, int i, int val) {
	if(heap[i].d > val)  {
		heap[i].d = val;
		while(i>0 && heap[parent(i)].d > heap[i].d) {
			swap(heap, i, parent(i));
			i = parent(i);
		}
	}
}

void minHeapify(hnode heap[], int i){
	int l, r, min;
	
	l= left(i);
	r= right(i);
	min=i;

	if(l<heapsz && heap[l].d<heap[min].d){
		min=l;
	}
	
	if(r<heapsz && heap[r].d<heap[min].d){
		min=r;
	}

	if(min!=i){
		swap(heap, min, i);
		minHeapify(heap, min);	
	}
}


void buildMinHeap(hnode heap[], int n){
	heapsz=n;
	int i;
	for(i=n/2;i>=0;i--){	
		minHeapify(heap, i);
	}
}


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

void addEdge(graph * g, int u, int v, int wt) {
	node * n = (node *)malloc(sizeof(node));
	n->v = v;
	n->wt = wt;
	n->next = g->adj[u];
	g->adj[u] = n;

	g->e = g->e + 1;
	
}	

void printGraph(graph * g) {
	int ver = g->v;
	int i;
	node * ele;
	for(i=0;i<ver;i++) {
		printf("%d :: ", i);	
		ele = g->adj[i];
		while(ele !=NULL) {
			printf("%d,%d --> ", ele->v, ele->wt);
			ele = ele->next;
		}
		printf("\n");
	}
}


void djk(graph *g, hnode *heap, int s){
	int cloud[g->v];
	int i, wt, v;
	node *ele;
	hnode h;

	int d[g->v];
	

	for(i=0;i<g->v;i++){
		cloud[i]=0;
		d[i] = 65536;	
	}

	while(heapsz!=0){
		
		h = extractMin(heap);
		printf("extracted :: %d\t%d\n", h.v + 1,  h.d);
		cloud[h.v] = 1;
		d[h.v] = h.d;	
		ele = g->adj[h.v];
		while(ele != NULL) {
			if(cloud[ele->v] == 0 ) {
				wt = ele->wt;
				for(i=0;i<heapsz;i++) {
					if(heap[i].v == ele->v)
						break;
				}
				if(heap[i].d > h.d + wt)
					decreaseKeyInHeap(heap, i, h.d + wt);
			}
			ele = ele->next;
		}
		
	}

	for(i=0;i<g->v;i++) {
		printf("%d\t%d\n", i+1,d[i]);
	}
}


int initDjk(graph * g, int s) {
	hnode *heap= (hnode*)malloc(g->v*sizeof(hnode));
	int i;

	for(i=0;i<g->v;i++){
		heap[i].v=i;
		heap[i].d= 65536;	
	}
	
	heap[s].d=0;
	
	buildMinHeap(heap, g->v);

	
	
	djk(g, heap, s);
}


int main(){
	int ver = 5;
	graph *g;
	g = initGraph(ver);
	
	
	addEdge(g, 0, 1, 10);
	addEdge(g, 0, 4, 5);
	addEdge(g, 1, 2, 1);
	addEdge(g, 1, 4, 2);
	addEdge(g, 2, 3, 6);
	addEdge(g, 3, 0, 7);
	addEdge(g, 3, 2, 6);
	addEdge(g, 4, 3, 2);
	addEdge(g, 4, 2, 9);
	addEdge(g, 4, 1, 3);
	printGraph(g);


	initDjk(g, 0);
			
}