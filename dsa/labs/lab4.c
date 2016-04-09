#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node n;

struct node {
	char lt;
	int frq;
	n *leftc, *rightc, *parent;
};

typedef struct heap_str heap;

struct heap_str {
	struct node **pt;
	int heap_size;
};

int heap_e_parent(i) {
	return ((i+1)/2) - 1;
}

int heap_e_left(i) {
	return (2*(i+1)) - 1;
}

int heap_e_right(i) {
	return (2*(i+1));
}

int min_heapify(struct heap_str *h, int loc) {
	int l = heap_e_left(loc);
	int r = heap_e_right(loc);
	int smallest;
	struct node *n;
	if(l<h->heap_size && (h->pt[l]->frq < h->pt[loc]->frq)) {
		smallest = l;
	}
	else {
		smallest = loc;
	}
	if(r < h->heap_size && (h->pt[r]->frq < h->pt[smallest]->frq)) {
		smallest = r;
	}
	if(smallest != loc) {
		n = h->pt[loc];
		h->pt[loc] = h->pt[smallest];
		h->pt[smallest] = n;
	}
}

int build_min_heap(struct heap_str *h) {
	int size = h->heap_size/2 , i;
	for(i=size;i>=0;i--) {
		min_heapify(h, i);
	}
}

int min_heap_insert(struct heap_str *h, struct node *n) {
	h->pt[h->heap_size] = n;
	h->heap_size = h->heap_size + 1;
	heap_decrease_key(h, h->heap_size - 1);
}

int heap_decrease_key(struct heap_str *h, int loc) {
	struct node *n;
	while(loc>0 && (h->pt[loc]->frq < (h->pt[heap_e_parent(loc)]->frq))) {
		n = h->pt[loc];
		h->pt[loc] = h->pt[heap_e_parent(loc)];
		h->pt[heap_e_parent(loc)] = n;
		loc = heap_e_parent(loc);
	}
}

struct node * heap_minimum(struct heap_str *h) {
	return h->pt[0];
}

struct node * heap_extract_minimum(struct heap_str *h) {
	struct node *min = h->pt[0];
	h->pt[0] = h->pt[h->heap_size - 1];
	h->heap_size = h->heap_size - 1;
	min_heapify(h, 0);
	return min;
}

int print(struct heap_str *h ) {
	int i = 0;
	struct node *tmp;
	for(i=0;i<h->heap_size;i++) {
		printf("%c, %d\n", h->pt[i]->lt, h->pt[i]->frq);
	}
}

int main() {
	char str[100];
	scanf("%s", &str);
	int l = strlen(str);

	struct node *ptr;
	ptr = (struct node *)malloc(l * sizeof(struct node *));

	struct heap_str h;
	h.pt = ptr;
	h.heap_size = 0;

	int i, j, k, cur_char, cur_freq, is_unique = 0;

	for(i=0;i<l;i++) {
		cur_char = str[i];
		cur_freq = 1;
		is_unique = 1;
		for(k=0;k<h.heap_size;k++) {
			if(h.pt[k]->lt == cur_char) {
				is_unique = 0;
				break;
			}
		}
		if(is_unique == 1) {
			for(j=i+1;j<l;j++) {
				if(cur_char == str[j]) {
					cur_freq++;
				}
			}
			struct node *n = (struct node *)malloc(sizeof(struct node));
			n->lt = cur_char;
			n->frq = cur_freq;
			n->leftc = NULL;
			n->rightc = NULL;
			n->parent = NULL;
			min_heap_insert(&h, n);
		}
	}

	struct node *pop1, *pop2, *push;
	while(h.heap_size > 1) {
		pop1 = heap_extract_minimum(&h);
		pop2 = heap_extract_minimum(&h);
		push = (struct node *)malloc(sizeof(struct node));
		
		push->lt = 48;
		push->frq = pop1->frq + pop2->frq;
		push->leftc = pop1;
		push->rightc = pop2;
		push->parent = NULL;

		pop1->parent = push;

		pop2->parent = push;
		
		min_heap_insert(&h, push);
	}

	printf("%d", count_nodes(h.pt[0])); 
	postorder_traversal(h.pt[0]);
	inorder_traversal(h.pt[0]);
	printHFCode(h.pt[0], str);
}

void printHFCode(struct node *n, char *msg) {
	char str[100], hfc[100][50];
	int count = 0; 
	int *i;
	i = &count;

	char *tmp, ltr;
	tmp = (char *)malloc(50 * sizeof(char));
	memset(tmp, '\0', 50);

	generateHFCode(n, str, hfc, i, tmp);

	int l = strlen(msg), p, q;

	for(p=0;p<l;p++) {
		ltr = msg[p];
		for(q=0;q<count;q++) {
			if(ltr == str[q]) {
				printf("%s", hfc[q]);
				break;
			}
		}
	}
}

generateHFCode(struct node *n, char *str, char hfc[100][50], int *i, char *form) {
	//printf("\nNODE INFO :: %x :: %c , %d , %x , %x , %x \n", n, n->lt, n->frq, n->leftc, n->rightc, n->parent);
	
	char *ctmp1, *ctmp2;
	ctmp1 = (char *)malloc(50 * sizeof(char));
	ctmp2 = (char *)malloc(50 * sizeof(char));
	memset(ctmp1, '\0', 50);
	memset(ctmp2, '\0', 50);
	strcpy(ctmp1, form);
	strcpy(ctmp2, form);

	if(n->leftc == NULL && n->rightc == NULL) {
		str[*i] = n->lt;
		strcpy(hfc[*i], form);
		*i = *i + 1;
	}
	else {
		if(n->leftc != NULL) {
			generateHFCode(n->leftc, str, hfc, i, strcat(ctmp1, "0"));
		}
		if(n->rightc != NULL) {
			generateHFCode(n->rightc, str, hfc, i, strcat(ctmp2, "1"));
		}
	}
}

int count_nodes(struct node *n) {
	int count = 0;
	if(n->leftc != NULL) {
		count += count_nodes(n->leftc);
	}
	if(n->rightc != NULL) {
		count += count_nodes(n->rightc);
	}
	count++;
	return count;
}

postorder_traversal(struct node *n) {
	if(n->leftc != NULL) {
		postorder_traversal(n->leftc);
	}
	if(n->rightc != NULL) {
		postorder_traversal(n->rightc);
	}
	printf("%c", n->lt);
}

inorder_traversal(struct node *n) {
	if(n->leftc != NULL) {
		inorder_traversal(n->leftc);
	}
	printf("%c", n->lt);
	if(n->rightc != NULL) {
		inorder_traversal(n->rightc);
	}
}

