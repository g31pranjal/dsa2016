#include <stdio.h>
#include <stdlib.h>

typedef struct node n;

struct node {
	int data;
	n *leftc;
	n *rightc;
	n *parent;
};

typedef struct queue q;

struct queue {
	n *list[1000];
	int front;
	int rear;
};

int Qadd(q *list, n *add) {
	list->list[list->rear++] = add;
}

n * Qremove(q *list) {
	return list->list[list->front++];
}

n * Qseek(q *list) {
	return list->list[list->front];
}

int addTreeNode(n **ref, q *list, int data) {
	n *nw = (n *)malloc(1*sizeof(n));
	nw->data = data;
	nw->leftc = NULL;
	nw->rightc = NULL;
	nw->parent = NULL;

	printf("%x\t", nw);
	
	if(list->front == list->rear) {
		*ref = nw;
		Qadd(list, nw);
		return 1;
	}
	else {
		n *parent = Qseek(list);
		if(parent->leftc == NULL) {
			parent->leftc = nw;
			nw->parent = parent;
			Qadd(list, nw);
			return 1;
		}
		else if(parent->rightc == NULL) {
			parent->rightc = nw;
			nw->parent = parent;
			Qadd(list, nw);
			Qremove(list);
			return 1;
		}

	}
}



int main() {

	q list;
	list.front = 0;
	list.rear = 0;

	n *root;

	int i;
	for(i=0;i<31;i++) {
		addTreeNode(&root, &list, 1);
	}

	printf("::%x\n", root->leftc->leftc);
	printf("::%x\n", root->leftc->rightc);

	printf("\n\n");

	for(i = list.front;i<list.rear;i++) {
		printf("%x\t", list.list[i]);
	}
}
