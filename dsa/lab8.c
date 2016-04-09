#include <stdio.h>
#include <stdlib.h>

typedef struct entry ent;

struct entry {
	char a[40];
	int h;
	int bf;
	ent *right, *left, *parent;
};


int wordcmp(char *a, char *b) {
	int al = strlen(a);
	int bl = strlen(b);
	int i = 0, r = -1;

	for(i=0;;i++) {
		if(i == al) {
			r = 2;
			break;
		}
		else if(i == bl) {
			r = 1;
			break;
		}
		else {
			if(a[i] > b[i]) {
				r = 1;
				break;
			}
			else if(a[i] < b[i]) {
				r = 2;
				break;
			}
			else 
				continue;
		}
	}
	return r;
}


int calchnbf(ent *node) {
	int hl, hr;
	
	if(node->left == NULL)
		hl = 0;
	else
		hl = (node->left)->h;

	if(node->right == NULL) 
		hr = 0;
	else
		hr = (node->right)->h;

	if(hl>hr)
		node->h = hl + 1;
	else 
		node->h = hr + 1;

	node->bf = hl - hr;
}


ent * tree_insert(ent **root, char *word) {
	ent *node = (ent *)malloc(sizeof(ent));

	memset(node->a, '\0' , sizeof(node->a));
	strcpy(node->a, word);
	node->left = NULL;
	node->right = NULL;
	node->parent = NULL;
	node->h = 1;
	node->bf = 0;

	ent *tmp1 = *root;
	ent *tmp2 = NULL;

	while(tmp1 != NULL) {
		tmp2 = tmp1;
		if(wordcmp(tmp1->a, node->a) == 2) 
			tmp1 = tmp1->right;	
		else 
			tmp1 = tmp1->left;
	}

	node->parent = tmp2;
	if(tmp2 == NULL) 
		*root = node;
	else {
		if(wordcmp(tmp2->a, node->a) == 2)
			tmp2->right = node;
		else 
			tmp2->left = node;
	}
	return node;

}

int tree_in_traverse(ent **root) {
	if(*root != NULL) {
		if((*root)->left != NULL)
			tree_in_traverse(&((*root)->left));
		printf("%s %d %d\n", (*root)->a, (*root)->h, (*root)->bf);
		if((*root)->right != NULL) 
			tree_in_traverse(&((*root)->right));
	}
}

int tree_pre_traverse(ent **root) {
	if(*root != NULL) {
		printf("%s %d %d\n", (*root)->a, (*root)->h, (*root)->bf);
		if((*root)->left != NULL) 
			tree_pre_traverse(&((*root)->left));
		if((*root)->right != NULL) 
			tree_pre_traverse(&((*root)->right));
	}
}


ent * findImbalance(ent * node) {
	while(node != NULL ) 
		if (node->bf == -2 || node->bf == 2)
			return node;
		else 
			node = node->parent;
	return node;
}

int calculateRotation(ent ** root, ent * node) {
	int h1l, h1r, h2l, h2r;
	ent *t1 = node;

	if(node->left == NULL) 
		h1l = 0;
	else 
		h1l = (node->left)->h;

	if(node->right == NULL)
		h1r = 0;
	else 
		h1r = (node->right)->h;

	if(h1r > h1l) {
		node = node->right;
		if(node->left == NULL) 
			h2l = 0;
		else 
			h2l = (node->left)->h;

		if(node->right == NULL) 
			h2r = 0;
		else 
			h2r = (node->right)->h;

		if(h2r > h2l) 
			rotateRR(root, t1, node, node->right);
		else 
			rotateRL(root, t1, node, node->left);																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																													
	}
	else {
		node = node->left;
		if(node->left == NULL) 
			h2l = 0;
		else 
			h2l = (node->left)->h;

		if(node->right == NULL) 
			h2r = 0;
		else 
			h2r = (node->right)->h;

		if(h2r > h2l) 
			rotateLR(root, t1, node, node->right);
		else 
			rotateLL(root, t1, node, node->left);
	}
}


int rotateRR(ent ** root, ent *a, ent *b, ent *c) {
	if(a->parent == NULL) {
		b->parent = NULL;
		*root = b;
	}
	else {
		if(a == (a->parent)->left) 
			(a->parent)->left = b;
		else if(a == (a->parent)->right) 
			(a->parent)->right = b;
		b->parent = a->parent;
	}
	if(b->left != NULL) {
		(b->left)->parent = a;
		a->right = b->left;
	}
	else 
		a->right = NULL;

	a->parent = b;
	b->left = a;

	while(a != NULL) {
		calchnbf(a);
		a = a->parent;
	}
}

int rotateRL(ent ** root, ent *a, ent *b, ent *c) {
	if(a->parent == NULL) {
		c->parent = NULL;
		*root = c;
	}
	else {
		if(a == (a->parent)->left)
			(a->parent)->left = c;
		else if(a == (a->parent)->right) 
			(a->parent)->right = c;
		c->parent = a->parent;
	}

	if(c->left != NULL) {
		(c->left)->parent = a;
		a->right = c->left;
	}
	else 
		a->right = NULL;

	if(c->right != NULL) {
		(c->right)->parent = b;
		b->left = c->right;
	}
	else
		b->left = NULL;

	a->parent = c;
	c->left = a;

	b->parent = c;
	c->right = b;

	calchnbf(a);
	calchnbf(b);
	while(a != NULL) {
		calchnbf(a);
		a = a->parent;
	}

}

int rotateLR(ent ** root, ent *a, ent *b, ent *c) {
	if(a->parent == NULL) {
		c->parent = NULL;
		*root = c;
	}
	else {
		if(a == (a->parent)->left)
			(a->parent)->left = c;
		else if(a == (a->parent)->right)
			(a->parent)->right = c;
		c->parent = a->parent;
	}

	if(c->left != NULL) {
		(c->left)->parent = b;
		b->right = c->left;
	}
	else 
		b->right = NULL;

	if(c->right != NULL) {
		(c->right)->parent = a;
		a->left = c->right;
	}
	else
		a->left = NULL;

	a->parent = c;
	c->left = b;

	b->parent = c;
	c->right = a;

	calchnbf(a);
	calchnbf(b);
	while(a != NULL) {
		calchnbf(a);
		a = a->parent;
	}
}

int rotateLL(ent ** root, ent *a, ent *b, ent *c) {
	if(a->parent == NULL) {
		b->parent = NULL;
		*root = b;
	}
	else {
		if(a == (a->parent)->left) 
			(a->parent)->left = b;
		else if(a == (a->parent)->right) 
			(a->parent)->right = b;
		b->parent = a->parent;
	}
	if(b->right != NULL) {
		(b->right)->parent = a;
		a->left = b->right;
	}
	else 
		a->left = NULL;

	a->parent = b;
	b->right = a;

	while(a != NULL) {
		calchnbf(a);
		a = a->parent;
	}
}

int main() {
	char gallery[100][40];
	int line = -1, i=0;
	ent *root, *node, *tmp2, *imbalance;
	
	do {
		line++;
		memset(gallery[line], '\0', sizeof(gallery[line]));
	}
	while(scanf("%s", gallery[line]) != -1);

	for(i = 0;i<line;i++) {
		imbalance = NULL;
		node = tree_insert(&root, gallery[i]);
		
		tmp2 = node;
		while(tmp2 != NULL) {
			calchnbf(tmp2);
			tmp2 = tmp2->parent;
		}

		imbalance = findImbalance(node);
		while(imbalance != NULL) {
			calculateRotation(&root, imbalance);
			imbalance = findImbalance(imbalance);
		}
	}
	tree_in_traverse(&root);
	tree_pre_traverse(&root);
	
	return 0;
}