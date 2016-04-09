#include <stdio.h>
#include <stdlib.h>


typedef struct node n;

struct node {
	long int num1, num2, ans, factor;
	int printed;
	n *c1, *c2, *c3, *parent;
};

typedef struct queue q;

struct queue {
	n *list[500];
	int front, rear;
};

int Qadd(q *list, n *add) {
	list->list[list->rear++] = add;
	return 0;
}

n * Qremove(q *list) {
	return list->list[list->front++];
}

n * Qseek(q *list) {
	return list->list[list->front];
}

n * Qseekr(q *list) {
	return list->list[(list->rear)-1];
}

typedef struct stack s;

struct stack {
	n *list[500];
	int front;
};

int Sadd(s *list, n *add) {
	list->list[list->front++] = add;
	return 0;
}

n * Sremove(s *list) {
	return list->list[--(list->front)];
}

n * Sseek(s *list) {
	return list->list[(list->front) - 1];
}

long int power(int n, int a) {
	int i;
	long int ans=1;
	for(i=0;i<a;i++) {
		ans=ans*n;
	}
	return ans;
}

int numLength(int num) {
	int digits = 0;
	while(num != 0) {
		digits++;
		num /= 10;
	}
	return digits;
}

n * addALeafNode(n **ref, q *Qlist , long int num1, long int num2, n *parent) {
	n *nw = (n *)malloc(1*sizeof(n));

	nw->num1 = num1;
	nw->num2 = num2;
	nw->ans = -1;
	nw->c1 = NULL;
	nw->c2 = NULL;
	nw->c3 = NULL;
	nw->parent = parent;
	nw->printed = 0;

	int nl1 = numLength(num1);
	int nl2 = numLength(num2);

	int larger;
	if(nl1 > nl2)
		larger = nl1;
	else
		larger = nl2;

	if(larger % 2 == 1) {
		larger += 1;
	}
	larger /= 2;

	long int factor = power(10, larger);
	nw->factor = factor;

	*ref = nw;
	Qadd(Qlist, nw);

	return nw;
}

int isLeafNode(n *node) {
	if((node->num1/10 == 0) && (node->num2/10 == 0))
		return 2;
	else
		return 1;
}

int decomposeNonLeafNode(n **ref, q *Qlist, n *node) {
	long int n1 = node->num1;
	long int n2 = node->num2;

	long int l1 = n1 % (node->factor);
	long int l2 = n2 % (node->factor);
	long int h1 = n1 / (node->factor);
	long int h2 = n2 / (node->factor);

	node->c1 = addALeafNode(ref, Qlist, h1+l1, h2+l2, node);
	node->c2 = addALeafNode(ref, Qlist, h1, h2, node);
	node->c3 = addALeafNode(ref, Qlist, l1, l2, node);

	return 0;
}

int main() {
	long int num1, num2, tmp;
	char temp;

	scanf("%d %c %d", &num1,&temp,&num2);

	struct node *root;

	q Qlist;
	Qlist.front = 0;
	Qlist.rear = 0;

	s Slist;
	Slist.front = 0;

	addALeafNode(&root, &Qlist, num1, num2, NULL);

	n *popped, *a, *b, *c, *pparent;
	while(Qlist.front != Qlist.rear) {
		popped = Qremove(&Qlist);
		if(isLeafNode(popped) == 2){
			Sadd(&Slist, popped);
		}
		else {
			decomposeNonLeafNode(&root, &Qlist, popped);
		}
	}

	while(Slist.front != 0) {
		Qadd(&Qlist, Sremove(&Slist));
	}

	while(Qlist.front != Qlist.rear) {
		popped = Qremove(&Qlist);
		popped->printed = 1;
		if(isLeafNode(popped) == 2) {
			popped->ans = popped->num1 * popped->num2;
			printf("%ldX%ld=%ld\n", popped->num1, popped->num2, popped->ans);
		}
		else {
			a = popped->c1;
			b = popped->c2;
			c = popped->c3;
			int factor = popped->factor;
			popped->ans = ((b->ans)*factor*factor) + ((a->ans - b->ans - c->ans)*factor) + c->ans;
			printf("%ldX%ld=%ldX%ldX%ld+(%ld-%ld-%ld)X%ld+%ld=%ld\n", popped->num1, popped->num2, b->ans, factor, factor, a->ans, b->ans, c->ans, factor, c->ans, popped->ans);
		}
		pparent = popped->parent;
		if(pparent != NULL) {
			if(pparent->c1->printed == 1 && pparent->c2->printed == 1 && pparent->c3->printed == 1 )
				Qadd(&Qlist, popped->parent);
		}
	}

	return 0;
}