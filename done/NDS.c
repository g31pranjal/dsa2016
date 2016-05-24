#include <stdlib.h>
#include <math.h>
#include <stdio.h>

typedef struct {
	int modv;
	int score;
} dictNode;

int insertionSort(dictNode *pt, int size) {
	int i,j,k,n,count = 0;

	for(k=1;k<size;k++) {
		dictNode res = pt[k];

		for(i=k-1;i>=0;i--) {
			if(pt[i].score < res.score) {
				pt[i+1] = pt[i];
			}
			else 
				break;

		}

		pt[i+1] = res;


	}

	return 0;
}

int main() {
	int n, k, count = 0, b;
	scanf("%d %d", &n, &k);

	int i, j,tmp;
	dictNode *com;
	com = (dictNode *)malloc(n*sizeof(dictNode));

	for(i=0;i<k;i++) {
		com[i].modv = i;
		com[i].score = 0;
	}

	for(i=0;i<n;i++) {
		scanf("%d", &tmp);
		tmp = tmp%k;
		com[tmp].score = com[tmp].score + 1;
	}

	insertionSort(com, k);

	// for(i=0;i<k;i++) {
	// 	printf("%d, %d\t", com[i].modv, com[i].score);
	// }
	// printf("\n");

	for(i=0;i<k;i++) {
		if(com[i].modv == 0 || (com[i].modv == k/2 && k%2 == 0))
			continue;
		else {
			count = count + com[i].score;	
			for(j=0;j<n;j++) {
				if(com[j].modv == k - com[i].modv) {
					com[j].score = 0;
				} 

			}
		}
		// for(b=0;b<k;b++) {
		// 	printf("%d, %d\t", com[b].modv, com[b].score);
		// }
		// printf("\n");

	}

	printf("%d\n", count);


}