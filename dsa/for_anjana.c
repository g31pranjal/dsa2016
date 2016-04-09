
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
		/* i had broken link in the following line */
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
