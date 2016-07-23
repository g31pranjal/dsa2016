#include <stdlib.h>
#include <math.h>
#include <stdio.h>

typedef struct treeNode tn;

struct treeNode {
	int key;
	tn *parent;
	
};


int main() {
	int n,m, t1, t2, i, j, parentAt = -1,hasParent = 0;
	scanf("%d %d", &n, &m);

	int arr[n][n];
	int par[n];
	int child[n];

	for(i=0;i<n;i++) {
		for(j=0;j<n;j++) {
			arr[i][j] = 0;
		}
		par[i] = -1;
		child[i] = 0;
	}

	//created adjacency matrix 
	for(i=0;i<m;i++) {
		scanf("%d %d", &t1, &t2);
		arr[t1-1][t2-1] = 1;
		arr[t2-1][t1-1] = 1;
	}

	
	

}