#include <stdlib.h>
#include <math.h>
#include <stdio.h>

typedef struct str s;

struct str {
	int dim;
	int walks;
	int *cur;
	int *dom;
};


typedef struct Node node;

struct Node {
	int *pos;
	int walk;
	int ans;
	node * next;
};

node **store;

int walk();

int addWalk(s* pt, int walks_left, int figure) {
	node *walkColl = store[walks_left - 1];
	int i;
	node * n = (node *)malloc(sizeof(node));
	n->pos = (int *)malloc(pt->dim*sizeof(int));
	for(i=0;i<pt->dim;i++) {
		n->pos[i] = pt->cur[i];
	}
	n->walk = walks_left;
	n->ans = figure;
	n->next = walkColl;
	store[walks_left - 1] = n;

	return 0;
} 

long search(s* pt, int walks_left) {


	node *walkColl = store[walks_left - 1];
	int found, i;
	long figure;
	int *pos;


	printf("searching ... \n");
	printf("walks left : %d\n", walks_left);
	printf("cur : ");
	for(i=0;i<pt->dim;i++) {
		printf("%d, ", pt->cur[i]);
	}
	printf("\n");


	found = 0;

	printf("store[%d]%x\n", walks_left - 1, store[walks_left-1]);

	while(walkColl != NULL) {
		printf("...........\n");
		pos = walkColl->pos;
		found = 1;
		for(i=0;i<pt->dim;i++) {
			if(pos[i] != pt->cur[i]) {
				found = 0;
				break;
			}
		}
		if(found == 1) {
			figure = walkColl->ans;
			break;
		}
		walkColl = walkColl->next;
	}

	if(found == 0) {
		figure = walk(pt, walks_left);
		addWalk(pt, walks_left, figure);
	}
	return figure;
}

long walk(s* pt, int walks_left) {
	int dim = pt->dim;
	long counts=0, i;

	printf("walks left : %d\n", walks_left);
	printf("cur : ");
	for(i=0;i<pt->dim;i++) {
		printf("%d, ", pt->cur[i]);
	}
	printf("store : ");
	for(i=0;i<pt->walks;i++) {
		printf("%x, ", store[i]);
	}
	printf("\n");

	if(walks_left == 1) {
		for(i=0;i<pt->dim;i++) {
			if(pt->cur[i] == 1 && pt->cur[i] < pt->dom[i]) {
				counts += 1;
			}
			else if(pt->cur[i] == pt->dom[i] && pt->cur[i] > 1) {
				counts += 1;
			}
			else if (pt->cur[i] < pt->dom[i] && pt->cur[i] > 1){
				counts += 2;
			}
		}
	}
	else {
		for(i=0;i<pt->dim;i++) {
			if(pt->cur[i] == 1 && pt->cur[i] < pt->dom[i]) {
				pt->cur[i]++;
				counts += search(pt, walks_left - 1) ;
				pt->cur[i]--;
			}
			else if(pt->cur[i] == pt->dom[i] && pt->cur[i] > 1) {
				pt->cur[i]--;
				counts += search(pt, walks_left - 1) ;
				pt->cur[i]++;
			}
			else {
				pt->cur[i]++;
				counts += search(pt, walks_left - 1) ;
				pt->cur[i]--;
				pt->cur[i]--;
				counts += search(pt, walks_left - 1) ;
				pt->cur[i]++;
			}
		}	
	}

	return counts;
}

int main() {
	int tc;
	scanf("%d", &tc);

	int i,j;
	s **data;
	data = (s **)malloc(tc*sizeof(s *));
	s *new;

	for(i=0;i<tc;i++) {
		new = (s *)malloc(sizeof(s));
		scanf("%d %d", &new->dim, &new->walks);
		new->cur = (int *)malloc(new->dim*(sizeof(int)));
		new->dom = (int *)malloc(new->dim*(sizeof(int)));
		for(j=0;j<new->dim;j++) {
			scanf("%d", &new->cur[j]);
		}
		for(j=0;j<new->dim;j++) {
			scanf("%d", &new->dom[j]);
		}

		data[i] = new;
	}


	for(i=0;i<tc;i++) {
		store = (node **)malloc(data[i]->walks*(sizeof(node *)));
		for(j=0;j<data[i]->walks;j++) {
			store[i] = NULL;
		}

		for(j=0;j<data[i]->walks;j++) {
			printf("%x\t", store[i]);
		}


		printf("%d\n", walk(data[i], data[i]->walks));
	}
}