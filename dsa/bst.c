#include <stdio.h>
#include <stdlib.h>

typedef struct Node node;

struct Node {
	int key;
	node * left, right, parent;
};


