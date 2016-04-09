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

	//printf("%d at node loc : %x" , pr, node);

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

	//printf(" .. parent  node loc : %x\n" , tmp2);

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

	int a, b, c, d, line = -1;

	char str[40];

	size_t length = 0;

	
	do {
		line++;
	}
	while(scanf("%d %d %d %d", &proc_details[line][0], &proc_details[line][1], &proc_details[line][2], &proc_details[line][3]) != -1);

/*	proc_details[0][0] = 1; proc_details[0][1] = 2; proc_details[0][2] = 2; proc_details[0][3] = 5;
	proc_details[1][0] = 2; proc_details[1][1] = 2; proc_details[1][2] = 1; proc_details[1][3] = 4;
	proc_details[2][0] = 3; proc_details[2][1] = 3; proc_details[2][2] = 1; proc_details[2][3] = 6;
	proc_details[3][0] = 4; proc_details[3][1] = 3; proc_details[3][2] = 2; proc_details[3][3] = 3;
*/

	int i=0;

	line = 4;

/*	for(i=0;i<line;i++) {
		printf("%d %d %d %d \n", proc_details[i][0], proc_details[i][1], proc_details[i][2], proc_details[i][3]);
	}*/

	ent *root = NULL, *mp, *t1;


	int ptr = 0, t = 0;

	while(t < proc_details[ptr][1]) {
		t++;
		printf("=============== process :: %d\n", 0);
		//printf("time incremented ! %d \n", t);
	}


	do {
		//printf("current time : %d \n", t);
		while(t == proc_details[ptr][1]) {
			tree_insert(&root, proc_details[ptr][0], proc_details[ptr][1], proc_details[ptr][2], proc_details[ptr][3]);
			//printf("node inserted : \n");
			ptr++;
		}

		if(root != NULL) {
			t1 = tree_maximum(root);
		}
		else {
			t1 = NULL;
		}
		
		if(t1 == NULL && mp != NULL) {
			mp->comp = mp->comp - 1;
			if(mp->comp == 0){
				//printf("checked ! \n");
				//printf("value of root : %d!", root);
				mp = NULL;
				break;
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
					//printf("process exhausted ! \n");
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

		printf("=============== process :: %d\n", mp->id);
		t++;

	} while(root != NULL || mp != NULL);






	


	//printf("\n\n line :: %d", line);

	
/*	tree_insert(&root, 0, 0, 0, 5);
	tree_insert(&root, 0, 0, 0, 1);
	tree_insert(&root, 0, 0, 0, 4);
	tree_insert(&root, 0, 0, 0, 3);
	tree_insert(&root, 0, 0, 0, 2);
*/
	//tree_traverse(&root);


	//printf("\n\n Searching 5 :: %x\n", tree_delete(&root, tree_search(root, 3))) ;

	//tree_traverse(&root);

}