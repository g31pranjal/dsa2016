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

int findMax(node * root) {
	if(root != NULL) {
		if(root->right == NULL)
			return root->key;
		else 
			findMax(root->right);
	}
}

int findMin(node * root) {
	if(root != NULL) {
		if(root->left == NULL)
			return root->key;
		else 
			findMax(root->left);
	}
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

	printf("min : %d\n", findMin(root));
}

