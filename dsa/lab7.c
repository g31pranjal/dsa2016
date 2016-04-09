#include <stdio.h>
#include <stdlib.h>

typedef struct entry ent;

struct entry {
	int id;
	int rel;
	int comp;
	int pr;
	ent *parent, *left, *right;
};

int tree_insert(ent **root, int id, int rel, int comp, int pr) {
	ent *node = (ent *)malloc(sizeof(ent));

	node->id = id;
	node->rel = rel;
	node->comp = comp;
	node->pr = pr;

	ent *tmp1 = *root;
	ent *tmp2 = NULL;

	while(tmp1 != NULL) {
		tmp2 = tmp1;
		if(tmp1->pr < node->pr) {
			tmp1 = tmp1->right;	
		}
		else {
			tmp1 = tmp1->left;
		}
	}

	node->parent = tmp2;

	if(tmp2 == NULL) {
		*root = node;
	}
	else {
		if(node->pr > tmp2->pr) {
			tmp2->right = node;
		}
		else {
			tmp2->left = node;
		}
	}
}

int tree_traverse(ent **root) {
	if(*root != NULL) {
		if((*root)->left != NULL) {
			tree_traverse(&((*root)->left));
		}
		printf("/%d", (*root)->pr);
		if((*root)->right != NULL) {
			tree_traverse(&((*root)->right));
		}
	}
}

ent * tree_search(ent *node, int pr) {
	while(node != NULL && node->pr != pr) {
		if (pr < node->pr) {
			node = node->left;
		}
		else {
			node = node->right;
		}
	}
	return node;
}

ent * tree_maximum(ent *x) {
	while(x->right != NULL) {
		x = x->right;
	}
	return x;
}

ent * tree_minimum(ent *x) {
	while(x->left != NULL) {
		x = x->left;
	}
	return x;
}

int tree_transplant(ent **root, ent *u, ent *v) {
	if(u->parent == NULL) {
		*root = v;
	} 
	else {
		if(u == (u->parent)->left) {
			(u->parent)->left = v;
		}
		else {
			(u->parent)->right = v;
		}
	}
	if(v != NULL) {
		v->parent = u->parent;
	} 
} 

int tree_delete(ent **root, ent *z) {
	if(z->left == NULL) {
		tree_transplant(root, z, z->right);
	}
	else if (z->right == NULL) {
		tree_transplant(root, z, z->left);
	}
	else {
		ent *y = tree_minimum(z->right);
		if(y->parent != z) {
			tree_transplant(root, y, y->right);
			y->right = z->right;
			(y->right)->parent = y;
		}
		tree_transplant(root, z, y);
		y->left = z->left;
		(y->left)->parent = y;
	}
}



int main() {
	int proc_details[100][4];
	int line = -1, ptr = 0, t = 0, i=0;
	ent *root = NULL, *mp = NULL, *t1 = NULL;

	do {
		line++;
	}
	while(scanf("%d %d %d %d", &proc_details[line][0], &proc_details[line][1], &proc_details[line][2], &proc_details[line][3]) != -1);

	while(t < proc_details[ptr][1]) {
		t++;
		printf("0\n");
	}


	do {
		while((ptr < line) && t == proc_details[ptr][1]) {
			tree_insert(&root, proc_details[ptr][0], proc_details[ptr][1], proc_details[ptr][2], proc_details[ptr][3]);
			ptr++;
		}

		if(root != NULL) {
			t1 = tree_maximum(root);
		}
		else {
			t1 = NULL;
		}



		if(t1 == NULL) {
			if(mp != NULL) {
				mp->comp = mp->comp - 1;
				if(mp->comp == 0){
					mp = NULL;
				}
			}
		}
		else {
			if(mp == NULL) {
				mp = t1;
				tree_delete(&root, t1);
			}
			else {
				mp->comp = mp->comp - 1;
				if(mp->comp == 0) {
					mp = t1;
					tree_delete(&root, t1);
				}
				else {
					if(mp != t1 && (mp->pr < t1->pr)) {
						tree_insert(&root, mp->id, mp->rel, mp->comp, mp->pr);
						mp = t1;
						tree_delete(&root, t1);
					}
				}
			}
		}
		
		if(mp != NULL) {
			printf("%d\n", mp->id);
		}
		else if (mp == NULL && (ptr < line || root != NULL)) {
			printf("0\n");
		}
		
		t++;

	} while(ptr < line || root != NULL || mp != NULL);

}