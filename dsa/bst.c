#include <stdio.h>
#include <stdlib.h>

typedef struct Node node;

struct Node {
	int key;
	node * left, * right, * parent;
};

node * insertNode(node * root, int val) {
	node * n = (node *)malloc(sizeof(node));
	n->key = val;
	n->left = NULL;
	n->right = NULL;
	n->parent = NULL;

	if(root == NULL) {
		return n;
	}
	else {
		if(root->key > val) {
			if(root->left == NULL) {
				n->parent = root;
				root->left = n;
			}
			else 
				insertNode(root->left, val);
		}
		else {
			if(root->right == NULL) {
				n->parent = root;
				root->right = n;
			}
			else 
				insertNode(root->right, val);
		}
		return root;
	}
}


node * findMax(node * root) {
	if(root != NULL) {
		if(root->right == NULL)
			return root;
		else 
			findMax(root->right);
	}
}

node * findMin(node * root) {
	if(root != NULL) {
		if(root->left == NULL)
			return root;
		else 
			findMin(root->left);
	}
}

node * searchNode(node * root, int val) {
	node * result;

	if(root == NULL) {
		return NULL;
	}
	else {
		if(root->key == val) {
			return root;
		}
		else if(root->key > val) {
			if(root->left == NULL)
				return NULL;
			else {
				result = searchNode(root->left, val);
			}
		}
		else {
			if(root->right == NULL)
				return NULL;
			else {
				result = searchNode(root->right, val);
			}	
		}
		return result;
	}
}

node * transplant(node * root, node * u, node *v) {
	
	if(u->parent == NULL) {
		root = v;
	}
	else {
		if(u->parent->left == u) 
			u->parent->left = v;
		else 
			u->parent->right = v;
		
		if(v != NULL) {
			v->parent = u->parent;
		}
	}

	return root;
}


node * deleteNode(node * root, int val) {
	node * z = searchNode(root, val);
	node * y;

	if(z != NULL) {
		if(z->left == NULL) {
			root = transplant(root, z, z->right);
		}
		else if(z->right == NULL) {
			root = transplant(root, z, z->left);
		}
		else {
			y = findMin(z->right);
			if(y->parent != z) {
				root = transplant(root, y, y->right);
				y->right = z->right;
				z->right->parent = y;
			}
			root = transplant(root, z, y);
			y->left = z->left;
			z->left->parent = y;
		}
	}

	return root;
}



void inorderTr(node * root) {
	if(root->left != NULL)
		inorderTr(root->left);
	printf("%d, ", root->key);
	if(root->right != NULL)
		inorderTr(root->right);
}




int main() {
	node * root;

	root = insertNode(root, 32);
	root = insertNode(root, 30);
	root = insertNode(root, 56);
	root = insertNode(root, 48);
	root = insertNode(root, 50);

	inorderTr(root);
	printf("\n");


	root = deleteNode(root, 32);

	inorderTr(root);
	printf("\n");

	root = deleteNode(root, 30);
	root = deleteNode(root, 56);

	inorderTr(root);


	root = deleteNode(root, 48);
	root = deleteNode(root, 50);


}

