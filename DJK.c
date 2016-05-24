#include <stdlib.h>
#include <stdio.h>
#include <math.h>


int djkCore(int **arr, int nov, int start) {

	int p[nov];
	int d[nov];

	int o[nov]

	int i, t;

	for(i=0;i<nov;i++) {
		p[i] = -1;
		d[i] = -1;
		o[i] = 0;				// 0 - vertex is in the priority queue
	}

	p[start] = -1;
	d[start] = 0;

	while(q->rear != q->front) {
		t = deQ(q);
		for(i=0;i<nov;i++) {
			if(arr[t][i] == 1) {
				if(s[i] == 0) {
					p[i] = t;
					d[i] = d[t] + 1;
					s[i] = 1;
					enQ(q, i);
				}
			}
		}
		s[t] = 2;

		
	}

	for(i=0;i<nov;i++) {
		if(d[i] !=0) {
			if(d[i] == -1)
				printf("-1 ");
			else
				printf("%d ", d[i]*6);
		}
	}
	printf("\n");


	return 0;


}



int main() {
	int tc;
	scanf("%d", &tc);

	int ***mn, *src, *nov;

	mn = (int ***)malloc(tc*sizeof(int **));
	src = (int *)malloc(tc*sizeof(int));
	nov = (int *)malloc(tc*sizeof(int));


	int i, noe, j, k, e1, e2, w;

	for(i=0;i<tc;i++) {
		scanf("%d", &nov[i]);
		scanf("%d", &noe);
		mn[i] = (int **)malloc(nov[i]*sizeof(int *));
		
		for(j=0;j<nov[i];j++) {
			mn[i][j] = (int *)malloc(nov[i]*sizeof(int));
			for(k=0;k<nov[i];k++) {
				mn[i][j][k] = 0;
			}
		}

		for(j=0;j<noe;j++) {
			scanf("%d %d %d", &e1, &e2, &w);
			mn[i][e1-1][e2-1] = w;
			mn[i][e2-1][e1-1] = w;
		}

		scanf("%d", &src[i]);
		src[i] = src[i] - 1;

	}

	for(i=0;i<tc;i++) {
		djkCore(mn[i], nov[i], src[i]);
	}

	return 0;

}