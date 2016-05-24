#include <stdlib.h>
#include <math.h>
#include <stdio.h>

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

	for(i=0;i<m;i++) {
		scanf("%d %d", &t1, &t2);
		arr[t1-1][t2-1] = 1;
		arr[t2-1][t1-1] = 1;
	}

	for(i=0;i<n;i++) {
		for(j=0;j<n;j++) {
			if(arr[i][j] == 1) {
				par[j] = i;
				arr[j][i] = 0;
			}
		}
	}

	for(i=0;i<n;i++) {
		if(par == -1) {
			parentAt = i;
			hasParent = 1;
			break;
		}
	}

	while(hasParent == 1) {
		nodes = 1;
		//parent node !!

		//calculate the number of childs 
		for(i=0;i<n;i++) {
			if(par[i] == parentAt) {
				nodes++;
			}
		}

















	}

}