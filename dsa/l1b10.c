#include <stdio.h>
#include <stdlib.h>

typedef struct Node node;

struct Node {
	int v;
	int edg;
	node * next;
};	

typedef struct Graph graph;

struct Graph {
	int v;
	int e;
	node **adj;
	int * vst;

};

graph * initGraph(num) {
	graph * g = (graph *)malloc(sizeof(graph));
	g->v = num;
	g->e = 0;
	g->adj = (node **)malloc(num*sizeof(node *));
	g->vst = (int *)malloc(num*sizeof(int));

	int i=0;
	for(i=0;i<num;i++){
		g->adj[i] = NULL;
		g->vst[i] = -1;
	}

	return g;
}

void addEdge(graph *g, int u, int v, int ed) {
	node *n = (node *)malloc(sizeof(node));
	n->v = v;
	n->edg = ed;
	n->next = g->adj[u];
	g->adj[u] = n;

	g->e = g->e + 1;
}

char * calcBin(int n) {
	int a1, bc, i=0, unit;
	
	char * bits = (char *)malloc(50*sizeof(char));
	
	for(i=0;i<50;i++) {
		bits[i] = '\0';
	}

	i=0;

	if(n==0) {
		return bits;
	} 
	else {
		//printf(" - in -         ");
		unit = 1;
		n = n - unit;
		for(i=1;n >= unit*2;i++) {
			unit = unit*2;
			n = n - unit;
		}
		
		bc = i;
		//printf("%d, %d , ", bc, n);

		for(i=bc-1;i>=0;i--) {
			bits[i] = '0';
		}

		
		//printf("%s  ", bits);


		do {
			a1 = n%2;
			if(a1 == 1) {
				bits[--bc] = '1';
				//printf("bc -> %d", bc);
				n--;
			}
			else {
				bits[--bc] = '0';
				//printf("bc -> %d", bc);

			}
			n = n/2;
			//printf("n -- %d , ", n);
		} while (n != 0);


		//printf("%s", bits);


	} 

/*
	bc = 0;

	a0 = n;
	do {
		bc++;
		a0 = a0/2;
	} while (a0 != 0);
	
	a2 = bc;
	a0 = n;
	do {
		a1 = a0%2;
		if(a1 == 1) {
			bits[--a2] = '1';
			a0--;
		}
		else {
			bits[--a2] = '0';
		}
		a0 = a0/2;
	} while (a0 != 0);
	*/
	return bits;
}


int rec(char * bits, int pt, int source, graph * g) {
	node * ele;
	//printf("%d, %d, %d\n", strlen(bits), pt, source);
	int t;
	if(pt == strlen(bits)) {
		//printf("border case -- >");
		if(g->vst[source] == 0)
			return 2;
		else 
			return 1;
	}
	else {
		ele = g->adj[source];
		

		while(ele != NULL) {
			if(ele->edg == bits[pt] - 48) {
				t = rec(bits, pt + 1, ele->v, g);
				if(t==1)
					return 1;
			}	
			ele = ele->next;

		}
	}

	return 2;
}


void main() {
	int ver, i, tmp1, tmp2, tmp3, j, tmp4, tmp5, resp;

	resp = scanf("%d", &ver);

	graph * g = initGraph(ver);

	for(i=0;i<ver;i++) {
		resp = scanf("%d", &tmp1);		// vertex number
		resp = scanf("%d", &tmp2);		// vertex state
		resp = scanf("%d", &tmp3);		// number of edges from the vertex

		g->vst[i] = tmp2;


		for(j=0;j<tmp3;j++) {
			resp = scanf("%d", &tmp4);
			resp = scanf("%d", &tmp5);
			tmp5 = tmp5 - 1;
			addEdge(g, i, tmp5, tmp4);
		}

	}


	//node * t1;

/*	for(i=0;i<ver;i++) {
		t1 = g->adj[i];
		while(t1 != NULL) {
			printf("%d, %d -- > ", t1->edg, t1->v);
			t1 = t1->next;
		}
		printf("\n");
	}


	for(i=0;i<ver;i++) {
		printf("%d\t", g->vst[i]);
	}

	printf("\n\n");*/


	int n = 0, a3, counter = 0;
	char * bits;
	
	for(n=0;;n++) {
		bits = calcBin(n);

		//printf("%s\n", bits);

		a3 = rec(bits, 0, 0, g);
		if(a3 == 1) {
			printf("%s", bits);
			counter++;
			if(counter == 10)
				break;
			else 
				printf("\n");
		}
	}


}